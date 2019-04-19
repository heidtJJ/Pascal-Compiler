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

extern int yyerror( char*);

RegisterStack* registerStack = NULL;

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

void setupRegisterStack(){
	registerStack = pushRegisterStr(NULL, "%edi");
//	registerStack = pushRegisterStr(registerStack, "%esi");
//	registerStack = pushRegisterStr(registerStack, "%edx");
	registerStack = pushRegisterStr(registerStack, "%ecx");
	registerStack = pushRegisterStr(registerStack, "%ebx");
//	registerStack = pushRegisterStr(registerStack, "%eax");
}

void freeRegisters(){
    freeRegisterStack(registerStack);
}

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
void getOffsetString(int frameOffset, char* offsetString){
    if(frameOffset > 0){
        sprintf(offsetString, "-%d(%%rbp)", frameOffset);
    }
    else{
        sprintf(offsetString, "%d(%%rbp)", -frameOffset);        
    }
}

/*
    Prints to offsetString a string of format: %offset(%rbp).
*/
void getVarOffset(int frameOffset, char* offsetString){
    
}


/*
    Outputs the x86 code to outFile to begin a procedure or function
    and load arguments into local variables.
*/
void genCodePrintProcBegin(FILE* outFile, scope_t* topScope){
    // Output subprogram name and begining code. 
    fputs(topScope->scopeOwner->name, outFile);
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
        getOffsetString(-offsetBelowBP, argOffsetString);

        // Create string for the argument from previous scope.
        char localOffsetString[12];
        getOffsetString(curArgument->frameOffset, localOffsetString);

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
    Returns the filename for a programId. fileName must be freed.
    Filename extension is ".s"
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
    Outputs code to outFile for moving value in arg1 to arg2.
*/
void genMovlCode(FILE* outFile, char* arg1, char* arg2){
    fputs("\tmovl\t", outFile);
    fputs(arg1, outFile);
    fputs(", ", outFile);
    fputs(arg2, outFile);
    fputs("\n", outFile);
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
        genExpression(outFile, argument, topScope);
        // Expression return value is now in top register.

        // Get location in string format for this argument.
        char argLocation[12];
        getOffsetString(basePointerOffset, argLocation);
        
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
    fputs(root->leftChild->attribute.nval->name, outFile);
    fputs("\n", outFile);
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

    }
    else if(root->type == ASSIGNOP){
        fprintf(stderr,"ASSIGNOP statement\n");
        tree_t* exprTree = root->rightChild;
        tree_t* varTree = root->leftChild;
        assert(exprTree != NULL);
        
        labelTree(exprTree, 1);// Setup expression tree for evaluation.
        genExpression(outFile, exprTree, topScope);// Generate code for expression.
        // Expression return value is now in top register.
        
        if(varTree->type == ID){
            node_t* idNode = varTree->attribute.nval;
            if(idNode->nodeType == FUNCTION){
                genMovlCode(outFile, registerStack->registerName, "%esi");                
            }
            else{
                char strOffset[12];// Could be dangerous. Rare that the offset has >12 characters though.
                getOffsetString(idNode->frameOffset, strOffset);
                assert(idNode->frameOffset != 0);
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
        fprintf(stderr,"WRITE statement\n");
        tree_print(root);

        tree_t* exprTree = root->leftChild;

        assert(exprTree != NULL);
        assert(exprTree->type != WRITE);
        
        labelTree(exprTree, 1);
        tree_label_print(exprTree);

        genExpression(outFile, exprTree, topScope);
        genPrintfCode(outFile, registerStack->registerName);
    }
    else if(root->type == READ){
        fprintf(stderr,"READ statement\n");
        tree_t* idTree = root->leftChild;
        assert(idTree != NULL && idTree->type == ID);
        char varLocation[12];
        getOffsetString(idTree->attribute.nval->frameOffset, varLocation);
        genReadCode(outFile, varLocation);
    }
    else{
        fprintf(stderr, "root->type %d\n", root->type);
        yyerror("root->type error in genStatement\n");
    }
}

/*
    Translates the value of the leaf into a string readable by x86 code.
*/
void getLeafString(tree_t* leaf, char* leafString, scope_t* topScope){
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
            getOffsetString(idNode->frameOffset, leafString);
        }
        else{
            // This variable is in a different scope. Must start chasing.
            getOffsetString(idNode->frameOffset, leafString);
        }
    }
    else{
        fprintf(stderr, "%d\n", leaf->type);
        assert(0);
    }
    return;
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
    else{
        fprintf(stderr, "operatorRoot->type %d\n", operatorRoot->type);
        fprintf(stderr, "operatorRoot->attribute.opval %d\n", operatorRoot->attribute.opval);
        assert(0);
    }
}

/*
    Writes to code for an operator with two operands. Division is 
    handled differently than other operators in x86.
*/
void writeOperatorCode(FILE* outFile, scope_t* topScope, tree_t* operatorRoot, char* arg1, RegisterStack* reg){
    if(operatorRoot->attribute.opval == SLASH){  
        // Move arg1 to temp location.
        char tempLocation[12];
        getOffsetString(topScope->tempsAddress, tempLocation);
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
        startSubprogram(outFile, operatorRoot, topScope);
        // Return value is in %eax.
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

void genCode(FILE* outFile, tree_t* root, scope_t* topScope){
    assert(registerStack != NULL);
    if(isLeaf(root) && root->label == 1){
        // Left Child
        fprintf(stderr, "CASE 0\n");
        
        char name[12];
        getLeafString(root, name, topScope);
        genMovlCode(outFile, name, registerStack->registerName);
        fputs("\n", outFile);    
    }
    else if(root->rightChild->label == 0){
        // Right Child
        fprintf(stderr, "CASE 1\n");

        genCode(outFile, root->leftChild, topScope);
        
        char name[12];
        getLeafString(root->rightChild, name, topScope);
        
        writeOperatorCode(outFile, topScope, root, name, registerStack);
        fputs("\n", outFile);    
    }
    else if(root->rightChild->label > root->rightChild->label){
        fprintf(stderr, "CASE 2\n");

        registerStack = swapRegisterStack(registerStack);
        genCode(outFile, root->rightChild, topScope);
        RegisterStack* poppedReg = popRegister(&registerStack);
        genCode(outFile, root->leftChild, topScope);
       
        writeOperatorCode(outFile, topScope, root, poppedReg->registerName, registerStack);

        registerStack = pushRegister(registerStack, poppedReg);
        registerStack = swapRegisterStack(registerStack);
        fputs("\n", outFile);    
    }
    else if(root->rightChild->label <= root->rightChild->label){
        fprintf(stderr, "CASE 3\n");

        genCode(outFile, root->leftChild, topScope);

        RegisterStack* poppedReg = popRegister(&registerStack);
        fprintf(stderr, "HERE %d %d\n", poppedReg, registerStack);
        
        genCode(outFile, root->rightChild, topScope);
        writeOperatorCode(outFile, topScope, root, registerStack->registerName, poppedReg);
    
        registerStack = pushRegister(registerStack, poppedReg);
        fputs("\n", outFile);    
    }
    else{
        assert(0);
    }
}

/*
    Tree is assumed to be already labeled. This is the gen_code algorithm.
*/
void genExpression(FILE* outFile, tree_t* root, scope_t* topScope){
    /* 
        Case where root is leaf. Should only happen when no operators.
        This is an exeption to the genCode algorithm.
    */
    if(isLeaf(root)){
        char name[12];
        fprintf(stderr, "LEAF EXPRESSIONNNN\n");
        getLeafString(root, name, topScope);
        genMovlCode(outFile, name, registerStack->registerName);
    }
    else if(root->type == FUNCTION_CALL){
        startSubprogram(outFile, root, topScope);
        genMovlCode(outFile, "%esi", registerStack->registerName);
        // Return value is in %eax.
    }
    else if(root->type == NOT){

    }
    else{
        int leftChildType = getExpressionType(topScope, root->leftChild);// INTEGER or REAL
        assert(leftChildType == REAL || leftChildType == INTEGER);
        if(leftChildType == INTEGER){
            genCode(outFile, root, topScope);
        }
        else{
            assert(0);
        }
    }
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
        labelTree(root->leftChild, 1);
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