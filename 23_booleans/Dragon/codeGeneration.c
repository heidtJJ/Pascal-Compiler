#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "codeGeneration.h"
#include "treeList.h"
#include "registerStack.h"
#include "y.tab.h"

/*
    %esi -> function return value register
    %eax -> division register
    %edx -> division register

    Diagram of runtime stack according to this compiler:

        HIGH MEMORY (each scope has a size of a multiple of 16 bytes. scanf requires this)
            reference address (1 word)
            old base pointer (1 word)
            local variables (X words)
            temp variables (Y words)
            arguments to called function (Z words)
        LOW MEMORY

*/

#define ARGUMENT_1_OFFSET 16
#define RBP "%rbp"

extern int yyerror( char*);
int getExpressionType(scope_t* curScope, tree_t* exprTree);

RegisterStack* registerStack = NULL;
RegisterStack* poppedRegisters = NULL;

int branchStringCounter = 0;

/* Top of assembly file */
char* topHeader = "\t.text\n\t.section\t.rodata\n.LC0:\n\t.string\t\"%d\\n\"\n\t.text\n\t.globl\tmain\n\t.type\tmain, @function\n.LC1:\n\t.string\t\"%d\"\n\t.text\n\t.globl\tmain\n\t.type\tmain, @function\n";

/* Assembly for creating functions/procedures. */
char* funcProcCodeBegin = "\tpushq\t%rbp\n\tmovq\t%rsp, %rbp\n";
char* funcProcCodeEnd = "\tleave\n\tret\n";
char* procedureEndInfo = "\n\t.globl\tmain\n\t.type\tmain, @function\n";

/* Code for printf assembly. */
char* printfEndCode = ", %esi\n\tleaq\t.LC0(%rip), %rdi\n\tmovl\t$0, %eax\n\tcall\tprintf\n";

/* Code for scanf assembly. */
char* scanfEndCode = ", %rax\n\tmovq\t%rax, %rsi\n\tleaq\t.LC1(%rip), %rdi\n\tmovl\t$0, %eax\n\tcall\t__isoc99_scanf@PLT\n";

/* Assembly for MAIN */
char* firstPartMainAsm = "main:\n\tpushq\t%rbp\n\tmovq\t%rsp, %rbp\n\tmovl\t$0, %eax\n";
// Needs "call	boo"
char* secondPartMainAsm = "\tmovl\t$0, %eax\n\tleave\n\tret\n";
char* mainInfoAsm = ".main:\n\t.size\tmain, .-main\n\t.ident\t\"GCC: (Ubuntu 8.2.0-7ubuntu1) 8.2.0\"\n\t.section\t.note.GNU-stack,\"\",@progbits\n";

char* my_itoa(int num, char *str){
    if(str == NULL){
        return NULL;
    }
    sprintf(str, "%d", num);
    return str;
}

/*
    Register stack is setup with only 3 registers.
*/
void setupRegisterStack(){
	registerStack = pushRegisterString(NULL, "%edi");
	registerStack = pushRegisterString(registerStack, "%ecx");
	registerStack = pushRegisterString(registerStack, "%ebx");
}

void freeRegisters(){
    freeRegisterStack(registerStack);
}

/*
    Prints the assembly headers to outFile. Look at topHeader.
*/
void genCodePrintHeader(FILE* outFile){
    fputs(topHeader, outFile);
}

/*
    Lowers the stack pointer to allow room for variables, temps, etc.
*/
void lowerStackPointer(FILE* outFile, int curScopeSize){
    fputs("\tsubq\t$", outFile);
    char strOffset[8];// Dangerous but rare for offset to have >8 characters.
    fputs(my_itoa(curScopeSize, strOffset), outFile);
    fputs(", %rsp # lowering the stack pointer.\n", outFile);
}

/*
    Prints to offsetString a string of format: %offset(%rbp).
*/
void getOffsetString(int frameOffset, char* offsetString, char* baseReg){
    if(frameOffset > 0){
        sprintf(offsetString, "-%d(%s)", frameOffset, baseReg);
    }
    else{
        sprintf(offsetString, "%d(%s)", -frameOffset, baseReg);        
    }
}

/*
    Outputs the MEAT of the movl x86 commands.
*/
void movHelper(FILE* outFile, char* arg1, char* arg2){
    fputs(arg1, outFile);
    fputs(", ", outFile);
    fputs(arg2, outFile);
    fputs("\n", outFile);
}

/*
    Outputs code to outFile to movq a value in arg1 to arg2.
*/
void genMovqCode(FILE* outFile, char* arg1, char* arg2){
    fputs("\tmovq\t", outFile);
    movHelper(outFile, arg1, arg2);
}

/*
    Outputs code to outFile to movl a value in arg1 to arg2.
*/
void genMovlCode(FILE* outFile, char* arg1, char* arg2){
    fputs("\tmovl\t", outFile);
    movHelper(outFile, arg1, arg2);
}


/*
    Outputs code to put the value in idNode into %eax. This variable
    could be outside of the current scope. If it is, then %rax must 
    chase the variable to its scope.
*/
void getVarOffset(FILE* outFile, node_t* idNode, char* offsetString, scope_t* topScope){
    assert(topScope != NULL);
    if(scope_search(topScope, idNode->name) != NULL ){
        // Variable is in current scope. 
        getOffsetString(idNode->frameOffset, offsetString, RBP);
    }
    else{
        // Variable is in a different scope. 
        short firstPass = 1;
        while(scope_search(topScope, idNode->name) == NULL){
            if(firstPass){
                // Move the base pointer to %rax on the first pass.
                genMovqCode(outFile, RBP, "%rax");
            }
            assert(topScope != NULL);
            topScope = topScope->next;
            genMovqCode(outFile, "(%rax)", "%rax");
            firstPass = 0;
        }
        getOffsetString(idNode->frameOffset, offsetString, "%rax");
    }
}

/*
    Outputs the x86 code to outFile to begin a procedure or function
    and load arguments into local variables.
*/
void genCodePrintProcBegin(FILE* outFile, scope_t* topScope){
    // Output subprogram name and begining code. 
    fputs(topScope->scopeName, outFile);
    fputs(":\n", outFile);
    fputs(funcProcCodeBegin, outFile);

    // Lower stack pointer for current scope on runtime stack.
    lowerStackPointer(outFile, topScope->curScopeSize);
    
    // Load arguments in previous scope to local variables on runtime stack.
    node_t* curArgument = topScope->scopeOwner->data.functionInfo.arguments;
    int offsetBelowBP = ARGUMENT_1_OFFSET;
    while(curArgument != NULL){
        // Create string for the argument from previous scope.
        char argOffsetString[12];
        getOffsetString(-offsetBelowBP, argOffsetString, RBP);

        // Create string for the argument from previous scope.
        char localOffsetString[12];
        getOffsetString(curArgument->frameOffset, localOffsetString, RBP);

        // Output code for moving argument to local variable.
        genMovlCode(outFile, argOffsetString, "%eax");
        genMovlCode(outFile, "%eax", localOffsetString);

        // Increase offset for next argument.
        offsetBelowBP += sizeof(int);
        curArgument = curArgument->next;
    }
}

/*
    Outputs code to end an x86 subprogram.
*/
void genCodePrintProcEnd(FILE* outFile, char* procName){
    fputs(funcProcCodeEnd, outFile);
    fputs(".", outFile);
    fputs(procName, outFile);
    fputs(":\n\t.size\t", outFile);
    fputs(procName, outFile);
    fputs(", .-", outFile);
    fputs(procName, outFile);
    fputs(procedureEndInfo, outFile);
}

/*
    Outputs code for the main function of a program.
*/
void genCodePrintMain(FILE* outFile, char* mainProcName){
    assert(outFile != NULL);
    fputs(firstPartMainAsm, outFile);
    fputs("\tcall\t", outFile);
    fputs(mainProcName, outFile);
    fputs("\n", outFile);
    fputs(secondPartMainAsm, outFile);
    fputs(mainInfoAsm, outFile);
}


/*
    Returns the filename for a programId. fileName must be freed
    later. Filename extension is ".s"
*/
char* getFileName(char* programId){
    int fileNameLen = strlen(programId) + 2; // +2 for .s 
    char* fileName = (char*) malloc(fileNameLen*sizeof(char));

    strcpy(fileName, programId);

    fileName[fileNameLen-2] = '.';
    fileName[fileNameLen-1] = 's';
    return fileName;
}

/*
    Outputs code to outFile for printing the value in stackLocation.
*/
void genPrintfCode(FILE* outFile, char* stackLocation){
    fputs("\tmovl\t", outFile);
    fputs(stackLocation, outFile);
    fputs(printfEndCode, outFile);
}

/*
    Outputs code to outFile for reading the value in stackLocation.
*/
void genReadCode(FILE* outFile, char* stackLocation){
    fputs("\tleaq\t", outFile);
    fputs(stackLocation, outFile);
    fputs(scanfEndCode, outFile);
}


void genPushqCode(FILE* outFile, char* locationToPush){
    fputs("\tpushq\t", outFile);
    fputs(locationToPush, outFile);
    fputs("\n", outFile);
}

void pushAllRegisters(FILE* outFile){
    genPushqCode(outFile, "%rdi");
    genPushqCode(outFile, "%rcx");
    genPushqCode(outFile, "%rbx");
}

void restoreAllRegisters(FILE* outFile){
    genMovqCode(outFile, "0(%rsp)", "%rbx");
    genMovqCode(outFile, "4(%rsp)", "%rcx");
    genMovqCode(outFile, "8(%rsp)", "%rdi");
    fputs("\taddq\t$12, %rsp\n", outFile);
}

/*
    Translates the value of the leaf into a string readable by x86 code.
*/
void getLeafString(FILE* outFile, tree_t* leaf, char* leafString, scope_t* topScope){
    assert(leaf->label == 0 || leaf->label == 1);
    if(leaf->type == INUM){
        sprintf(leafString, "$%d", leaf->attribute.ival);
    }
    else if(leaf->type == RNUM){
        assert(0);
    }
    else if(leaf->type == ID){
        node_t* idNode = leaf->attribute.nval;
        if(scope_search(topScope, idNode->name) != NULL){
            // This variable is in the current scope.
            getOffsetString(idNode->frameOffset, leafString, RBP);
        }
        else{
            // This variable is in a different scope. Must start chasing.
            getVarOffset(outFile, leaf->attribute.nval, leafString, topScope);
        }
    }
    else{
        fprintf(stderr, "%d\n", leaf->type);
        assert(0);
    }
    return;
}

/*
    Labels the expression tree to prepare it for 
    genExpression (gen_code).
*/
void labelTree(tree_t* root, short isLeftMost){
    // For now, assume no functions or NOT.
    if(root == NULL){
        assert(0);
        return;
    }
    // Leaf case should only happen when no operators.
    else if(isLeaf(root)){
        fprintf(stderr, "%d\n", root->type);
        root->label = 1;
        return;
    }
    // NOT case should make current node have child's label
    else if(root->type == NOT){
        labelTree(root->leftChild, isLeftMost);
        root->label = root->leftChild->label;
        return;
    }
    // For function call, label is the max label of the expression arguments. 
    else if(root->type == FUNCTION_CALL){
        // Retrieve the argument list for this function.
        TreeList* curArgument = root->rightChild->attribute.listVal;
        int maxLabel = isLeftMost;
        while(curArgument != NULL){
            // Retrieve the expression tree from this argument.
            tree_t* curArgumentExpr = curArgument->statementTree;
            labelTree(curArgumentExpr, isLeftMost);
            
            // Update the max label based on label of expression tree.
            maxLabel = curArgumentExpr->label > maxLabel ? curArgumentExpr->label : maxLabel;
            curArgument = curArgument->next;
        }
        root->label = maxLabel;
    }
    else if(root->type == ARRAY_ACCESS){
        assert(0);
    }
    else{
        // Handle left child.
        if(hasLeftLeaf(root)){
            root->leftChild->label = 1;
        }
        else{
            labelTree(root->leftChild, 1);
        }
        // Handle right child.
        if(hasRightLeaf(root)){
            root->rightChild->label = 0;
        }
        else{
            labelTree(root->rightChild, 0);
        }
        
        int leftChildLabel = root->leftChild->label;
        int rightChildLabel = root->rightChild->label;
        // Handle root.
        if(leftChildLabel == rightChildLabel){
            root->label = leftChildLabel+1;
        }
        else{
            // TO-DO: make max function.
            root->label = leftChildLabel > rightChildLabel ? leftChildLabel : rightChildLabel;
        }
    }
}


/*
    Outputs code to outFile for starting a procedure or 
    function. Arguments are put into position and the next
    function is called. 
*/
void startSubprogram(FILE* outFile, tree_t* root, scope_t* topScope){
    // Retrieve argument list from tree node.    
    TreeList* curArgument = root->rightChild->attribute.listVal;
    
    // Initialize the offset from the base pointer to the first
    // argument position.
    int basePointerOffset = topScope->curScopeSize;
    while(curArgument != NULL){
        tree_t* argument = curArgument->statementTree;

        // Setup expression tree for evaluation.
        labelTree(argument, 1);
        // Generate code for expression.
        genExpression(outFile, argument, topScope, 1);
        // Expression return value is now in top register.

        // Get location in string format for this argument.
        char argLocation[12];
        getOffsetString(basePointerOffset, argLocation, RBP);
        
        // Move the expression return value into the argument position.
        genMovlCode(outFile, registerStack->registerName, "%eax");
        genMovlCode(outFile, "%eax", argLocation);
        
        // Increase base pointer and move to next argument. 
        basePointerOffset += 4;
        curArgument = curArgument->next;
    }
    // Set the return value to 0 before calling subprogram.
    genMovlCode(outFile, "$0", "%esi");

    // Call subprogram.
    fputs("\tcall\t", outFile);
    fputs(topScope->scopeName, outFile);
    fputs("_", outFile);
    fputs(root->leftChild->attribute.nval->name, outFile);
    fputs("\n", outFile);
}


/*
    Prints the associated operator with operatorRoot to operatorString.
    This currenly ONLY works with INTEGERS
*/
void getOperatorString(tree_t* operatorRoot, char* operatorString){
    assert(operatorRoot->type == MULOP || operatorRoot->type == ADDOP || operatorRoot->type == RELOP );
    if(operatorRoot->attribute.opval == PLUS){
        sprintf(operatorString, "addl");
    }
    else if(operatorRoot->attribute.opval == MINUS){
        sprintf(operatorString, "subl");
    }
    else if(operatorRoot->attribute.opval == STAR){
        sprintf(operatorString, "imull");
    }
    else if(operatorRoot->attribute.opval == SLASH){
        sprintf(operatorString, "idivl");
    }
    else if(operatorRoot->attribute.opval == AND){
        sprintf(operatorString, "andl");
    }
    else if(operatorRoot->attribute.opval == OR){
        sprintf(operatorString, "orl");
    }
    else{
        fprintf(stderr, "operatorRoot->type %d\n", operatorRoot->type);
        fprintf(stderr, "operatorRoot->attribute.opval %d\n", operatorRoot->attribute.opval);
        assert(0);
    }
}

/*
    Outputs the code to compare two values. Values can be in
    memory or a register.
*/
void printCompareCode(FILE* outFile, char* arg1, char* arg2){
    fputs("\tcmpl\t", outFile);
    fputs(arg1, outFile);
    fputs(", ", outFile);
    fputs(arg2, outFile);
    fputs("\n", outFile);
}

/*
    Prints the x86 assembly code for a relative operation (boolean 1 or 0).
*/
void printRelopCode(FILE* outFile, tree_t* operatorRoot, char* arg1, RegisterStack* reg){
    // Print the code to setup operation.
    printCompareCode(outFile, arg1, reg->registerName);
    fputs("\t", outFile);
    // Print specific operation command.
    switch(operatorRoot->attribute.opval){
        case EQ:
            fputs("setz", outFile);
            break;
        case NE:
            fputs("setne", outFile);
            break;
        case LT:
            fputs("setl", outFile);
            break;
        case LE:
            fputs("setle", outFile);
            break;
        case GT:
            fputs("setg", outFile);
            break;
        case GE:
            fputs("setge", outFile);
            break;
        default:
            assert(0);
    }
    
    fputs("\t%al\n\tmovzbl\t%al, ", outFile);
    fputs(reg->registerName, outFile);
    fputs("\n", outFile);
}

/*
    Writes to code for an operator with two operands. Division is 
    handled differently than other operators in x86.
*/
void writeOperatorCode(FILE* outFile, scope_t* topScope, tree_t* operatorRoot, char* arg1, RegisterStack* reg){
    if(operatorRoot->attribute.opval == SLASH){  
        // Move arg1 to temp location.
        char tempLocation[12];
        getOffsetString(topScope->tempsAddress, tempLocation, RBP);
        genMovlCode(outFile, arg1, "%eax");
        genMovlCode(outFile, "%eax", tempLocation);
        
        // Move value in reg to the division register, %eax.
        genMovlCode(outFile, reg->registerName, "%eax");
        fputs("\tcltd\n", outFile);
        
        // Output division code.
        fputs("\tidivl\t", outFile);
        fputs(tempLocation, outFile);
        fputs("\n", outFile);

        // Move result to top of registerStack.
        genMovlCode(outFile, "%eax", reg->registerName);
    }
    else if(operatorRoot->type == FUNCTION_CALL){
        // This case should not happen?
        assert(0);
        startSubprogram(outFile, operatorRoot, topScope);
        // Return value is in reg.
    }
    else if(operatorRoot->type == RELOP){
        printRelopCode(outFile, operatorRoot, arg1, reg);
        // Return value is in reg.
    }
    else{
        // Create a string for the operator to be applied.
        char operatorString[12];
        getOperatorString(operatorRoot, operatorString);

        // Output the code to execute the operator on the operands.
        fputs("\t", outFile);    
        fputs(operatorString, outFile); 
        fputs("\t", outFile);    
        fputs(arg1, outFile);    
        fputs(", ", outFile);    
        fputs(reg->registerName, outFile);    
        fputs("\n", outFile);  
    }  
}

/*
    Tree is assumed to be already labeled. This is the gen_code algorithm.
*/
void genExpression(FILE* outFile, tree_t* root, scope_t* topScope, short isLeftMost){
    // Leaf case.
    if(isLeaf(root)){
        fprintf(stderr, "CASE 0\n");

        // Check for leftMost leaf.
        if(isLeftMost){
            fprintf(stderr, "Top Register %s\n", registerStack->registerName);

            char name[12];
            getLeafString(outFile, root, name, topScope);
            fprintf(stderr, "Name: %s\n", name);
            genMovlCode(outFile, name, registerStack->registerName);
        }
        else{ assert(0); }
    }
    // Non-Leaf cases.
    else if(root->type == FUNCTION_CALL){        
        // Put all remaining registers on the runtime stack.
        fputs("# Putting regs on the stack.\n", outFile);
        pushAllRegisters(outFile);
        fputs("# Done putting regs on the stack.\n", outFile);

        // Call function.
        startSubprogram(outFile, root, topScope);
        
        fputs("# Restoring regs on the stack.\n", outFile);
        // Restore registers
        restoreAllRegisters(outFile);
        fputs("# Done restoring regs on the stack.\n", outFile);

        // Return value is now in %esi.
        genMovlCode(outFile, "%esi", registerStack->registerName);
    }
    else if(root->type == NOT){
        // In boolean expressions, values should either be 1 or 0.
        // So, we can just xor the value with 1 to flip the bit.
	   
        // First retrieve the boolean result of the left child.
        genExpression(outFile, root->leftChild, topScope, isLeftMost);

        fputs("\txor\t$1, ", outFile);
        fputs(registerStack->registerName, outFile);
        fputs("\n", outFile);
        // Result now sits on top of register stack.
    }
    else{
        assert(root->type == RELOP || root->type == ADDOP || root->type == MULOP);

        // Root is an operator.
        int leftChildType = getExpressionType(topScope, root->leftChild);
        assert(leftChildType == INTEGER);// For now
        
        tree_t* leftChild = root->leftChild;
        tree_t* rightChild = root->rightChild;
        if(rightChild->label == 0){
            // Right Child
            fprintf(stderr, "CASE 1\n");

            genExpression(outFile, leftChild, topScope, 1);
            
            char name[12];
            getLeafString(outFile, rightChild, name, topScope);            

            writeOperatorCode(outFile, topScope, root, name, registerStack);
            fputs("\n", outFile);    
        }
        else if(rightChild->label > rightChild->label){
            fprintf(stderr, "CASE 2\n");

            registerStack = swapRegisterStack(registerStack);
            genExpression(outFile, rightChild, topScope, 0);
            
            RegisterStack* poppedReg = popRegister(&registerStack);
            poppedRegisters = pushRegister(poppedRegisters, poppedReg);
            
            fprintf(stderr, "POPPED %s\n", poppedReg->registerName);

            genExpression(outFile, leftChild, topScope, 1);
        
            writeOperatorCode(outFile, topScope, root, poppedReg->registerName, registerStack);

            registerStack = pushRegister(registerStack, poppedReg);
            registerStack = swapRegisterStack(registerStack);
            poppedRegisters = popRegister(&poppedRegisters);

            fputs("\n", outFile);    
        }
        else if(leftChild->label <= rightChild->label){
            fprintf(stderr, "CASE 3\n");

            genExpression(outFile, leftChild, topScope, 1);

            RegisterStack* poppedReg = popRegister(&registerStack);
            poppedRegisters = pushRegister(poppedRegisters, poppedReg);

            fprintf(stderr, "POPPED %s\n", poppedReg->registerName);
            
            genExpression(outFile, rightChild, topScope, 0);
            writeOperatorCode(outFile, topScope, root, registerStack->registerName, poppedReg);
        
            registerStack = pushRegister(registerStack, poppedReg);
            poppedRegisters = popRegister(&poppedRegisters);
            fputs("\n", outFile);    
        }
        else{
            assert(0);
        }
    }
}

char* getBranchString(int count){
    // 2 for .L, and 1 for \0 (from sprintf).
    int branchStringSize = 2 + countDigits(branchStringCounter);
    char* branchString = (char*) malloc((branchStringSize+1)*sizeof(char));
    sprintf(branchString, ".L%d", count);
    return branchString;
}

/*
    Branching is used for executing if-then-else statements.
    This function generates the code for those.
*/
void genIfBranching(FILE* outFile, tree_t* root, scope_t* topScope){
    assert(root->type == THEN);

    // If expression returned 0, jump to another location. Else continue.
    printCompareCode(outFile, "$0", registerStack->registerName);
    
    // If rightChild is NULL, there is no else statement.
    if(root->rightChild == NULL){
        // Get string for the jump location.
        char* branchString = getBranchString(branchStringCounter++);

        // Generate branching code.
        fputs("\tje\t", outFile);  
        fputs(branchString, outFile);  
        fputs("\n", outFile); 
        genStatement(outFile, root->leftChild, topScope);
        fputs(branchString, outFile); 
        fputs("\n", outFile); 

        // Deallocate the branchString.
        free(branchString);
    }
    else{
        // There is an else.
        char* elseBranchString = getBranchString(branchStringCounter++);
        char* endBranchString = getBranchString(branchStringCounter++);
        
        // Generate branching code.
        fputs("\tje\t", outFile);  
        fputs(endBranchString, outFile);  
        fputs("\n", outFile); 

        // Generate then statements.
        genStatement(outFile, root->leftChild, topScope);

        // Jump to end of else statement.
        fputs("\tjmp\t", outFile);  
        fputs(endBranchString, outFile); 
        fputs("\n", outFile);

        // Indicate the location of the else statement.
        fputs(elseBranchString, outFile); 
        fputs("\n", outFile);

        // Generate else statement.
        genStatement(outFile, root->rightChild, topScope);

        // Indicate the end of branching location.
        fputs(endBranchString, outFile); 
        fputs("\n", outFile);

        // Deallocate.
        free(elseBranchString);
        free(endBranchString);
    }
}

/*
    Generates the code for executing statements.
*/
void genStatement(FILE* outFile, tree_t* root, scope_t* topScope){
    if(root == NULL){
        return;
    }
    else if(root->type == PROCEDURE_CALL){
        startSubprogram(outFile, root, topScope);
    }
    else if(root->type == IF){
        // Left side is boolean expression
        tree_t* exprTree = root->leftChild;

        // Setup expression tree for code generation.
        labelTree(exprTree, 1);
        // Evaulate the expression.
        genExpression(outFile, exprTree, topScope, 1);
        // Expression return value is now in top register.

        // Write the branching statements.
        genIfBranching(outFile, root->rightChild, topScope);
    }
    else if(root->type == ASSIGNOP){
        fprintf(stderr,"ASSIGNOP statement\n");
        tree_t* exprTree = root->rightChild;
        tree_t* varTree = root->leftChild;
        assert(varTree != NULL && exprTree != NULL);
        
        // Setup expression tree for code generation.
        labelTree(exprTree, 1);
        genExpression(outFile, exprTree, topScope, 1);
        // Expression return value is now in top register.
        
        // Check if the variable is an ID or array.
        if(varTree->type == ID){
            node_t* idNode = varTree->attribute.nval;
            if(idNode->nodeType == FUNCTION){
                // This sets up the "return" statement for functions.
                genMovlCode(outFile, registerStack->registerName, "%esi");                
            }
            else{
                // Sets the value of a variable. Could be in another scope (another stack frame).
                assert(idNode->frameOffset != 0);
                char strOffset[12];// Could be dangerous but rare for offset >12 characters.
                getVarOffset(outFile, idNode, strOffset, topScope);
                genMovlCode(outFile, registerStack->registerName, strOffset);
            }
        }
        else{// varTree->type == ARRAY_ACCESS
            assert(varTree->type == ARRAY_ACCESS);
        }
    }
    else if(root->type == WHILE){
        
    }
    else if(root->type == FOR){
        
    }
    else if(root->type == WRITE){
        fprintf(stderr, "WRITE statement\n");
        tree_print(root);

        tree_t* exprTree = root->leftChild;

        assert(exprTree != NULL);
        assert(exprTree->type != WRITE);
        
        // Setup expression tree for code generation.
        labelTree(exprTree, 1);
        // Execute code generation.
        genExpression(outFile, exprTree, topScope, 1);
        // Value to print is now in the top register.
        genPrintfCode(outFile, registerStack->registerName);
    }
    else if(root->type == READ){
        fprintf(stderr,"READ statement\n");
        tree_t* idTree = root->leftChild;
        assert(idTree != NULL && idTree->type == ID);
        char varLocation[12];
        getVarOffset(outFile, idTree->attribute.nval, varLocation, topScope);
        genReadCode(outFile, varLocation);
    }
    else{
        fprintf(stderr, "root->type %d\n", root->type);
        yyerror("root->type error in genStatement\n");
    }
}
