#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "codeGeneration.h"
#include "treeList.h"
#include "registerStack.h"
#include "y.tab.h"

extern int yyerror( char*);

RegisterStack* registerStack = NULL;

/* Top of assembly file */
char* topHeader = "\t.text\n\t.section\t.rodata\n.LC0:\n\t.string\t\"%d\\n\"\n\t.text\n\t.globl\tmain\n\t.type\tmain, @function\n.LC1:\n\t.string\t\"%d\"\n\t.text\n\t.globl\tmain\n\t.type\tmain, @function\n";

/* Assembly for creating functions/procedures. */
char* procedureCodeBegin = "\tpushq\t%rbp\n\tmovq\t%rsp, %rbp\n";
char* procedureCodeEnd = "\tleave\n\tret\n";
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
	registerStack = pushRegisterStr(NULL, "%r15");
	registerStack = pushRegisterStr(registerStack, "%r14");
	registerStack = pushRegisterStr(registerStack, "%r13");
	registerStack = pushRegisterStr(registerStack, "%r12");
	registerStack = pushRegisterStr(registerStack, "%r11");
	registerStack = pushRegisterStr(registerStack, "%r10");
	registerStack = pushRegisterStr(registerStack, "%r9");
	registerStack = pushRegisterStr(registerStack, "%r8");
	registerStack = pushRegisterStr(registerStack, "%edi");
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

void lowerStackPointer(FILE* outFile, int curScopeSize){
    // Example: subq	$32, %rsp
    fputs("\tsubq\t$", outFile);
    char strOffset[8];// Could be dangerous. Rare that the offset has >8 characters though.
    fputs(my_itoa(curScopeSize, strOffset), outFile);
    fputs(", %rsp # lowering the stack pointer.\n", outFile);
}

void genCodePrintProcBegin(FILE* outFile, char* procName, scope_t* topScope){
    fputs(procName, outFile);
    fputs(":\n", outFile);
    fputs(procedureCodeBegin, outFile);
    lowerStackPointer(outFile, topScope->curScopeSize);
}

void genCodePrintProcEnd(FILE* outFile, char* procName){
    fputs(procedureCodeEnd, outFile);
    fputs(".", outFile);
    fputs(procName, outFile);
    fputs(":\n\t.size\t", outFile);
    fputs(procName, outFile);
    fputs(", .-", outFile);
    fputs(procName, outFile);
    fputs(procedureEndInfo, outFile);
}

void genCodePrintMain(FILE* outFile, char* mainProcName){
    assert(outFile != NULL);
    fputs(firstPartMainAsm, outFile);
    fputs("\tcall\t", outFile);
    fputs(mainProcName, outFile);
    fputs("\n", outFile);
    fputs(secondPartMainAsm, outFile);
    fputs(mainInfoAsm, outFile);
}


char* getFileName(char* programId){
    int fileNameLen = strlen(programId) + 2; /* +2 for .s */
    char* fileName = (char*) malloc(fileNameLen*sizeof(char));

    fprintf(stderr, "programId: %s\n", programId);
    strcpy(fileName, programId);

    fileName[fileNameLen-2] = '.';
    fileName[fileNameLen-1] = 's';
    return fileName;
}

void genMovlCode(FILE* outFile, char* arg1, char* arg2){
    fputs("\tmovl\t", outFile);
    char strInum[8];// Could be dangerous. Rare for arg to have >8 characters though.
    fputs(arg1, outFile);
    fputs(", ", outFile);
    fputs(arg2, outFile);
    fputs("  # moved register values\n", outFile);
}

void genPrintfCode(FILE* outFile, char* stackLocation){
    fputs("\tmovl\t", outFile);
    fputs(stackLocation, outFile);
    fputs(printfEndCode, outFile);
}

void genReadCode(FILE* outFile, char* stackLocation){
    fputs("\tleaq\t", outFile);
    fputs(stackLocation, outFile);
    fputs(scanfEndCode, outFile);
}

void getOffsetString(int frameOffset, char* offsetString){
    if(frameOffset > 0){
        sprintf(offsetString, "-%d(%%rbp)", frameOffset);
    }
    else{
        sprintf(offsetString, "%d(%%rbp)", frameOffset);        
    }
}

void genStatement(FILE* outFile, tree_t* root, scope_t* topScope){
    if(root == NULL){
        return;
    }
    else if(root->type == PROCEDURE_CALL){
        // Set up procedure call.
        // Put values in args.
        TreeList* curArgument = root->attribute.listVal;
        
        int basePointerOffset = topScope->curScopeSize-(curArgument->listLength*4);
        while(curArgument != NULL){
            tree_t* argument = curArgument->statementTree;
            labelTree(argument);// Setup expression tree for evaluation.
            genExpression(outFile, argument, topScope);// Generate code for expression.
            
            // Expression return value is now in top register.
            char argLocation[12];
            getOffsetString(basePointerOffset, argLocation);
            genMovlCode(outFile, registerStack->registerName, "%eax");
            genMovlCode(outFile, "%eax", argLocation);

        }
    }
    else if(root->type == IF){

    }
    else if(root->type == ASSIGNOP){
        fprintf(stderr,"ASSIGNOP statement\n");
        tree_t* exprTree = root->rightChild;
        tree_t* varTree = root->leftChild;
        assert(exprTree != NULL);
        
        labelTree(exprTree);// Setup expression tree for evaluation.
        genExpression(outFile, exprTree, topScope);// Generate code for expression.
        // Expression return value is now in top register.
        
        if(varTree->type == ID){
            node_t* idNode = varTree->attribute.nval;
            char strOffset[12];// Could be dangerous. Rare that the offset has >12 characters though.
            getOffsetString(idNode->frameOffset, strOffset);
            genMovlCode(outFile, registerStack->registerName, strOffset);
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
        
        labelTree(exprTree);
        fprintf(stderr, "%d\n", exprTree->leftChild);
        fprintf(stderr, "%d\n", exprTree->rightChild);
        fprintf(stderr, "%d\n", exprTree->type);
        tree_label_print(exprTree);

        genExpression(outFile, exprTree, topScope);
        // Expression return value is now in top register.
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
        getOffsetString(idNode->frameOffset, leafString);
    }
    else{
        fprintf(stderr, "%d\n", leaf->type);
        assert(0);
    }
    return;
}


void getOperatorString(tree_t* operatorRoot, char* operatorString){
    assert(operatorRoot->type == MULOP || operatorRoot->type == ADDOP || operatorRoot->type == RELOP );
    if(operatorRoot->attribute.opval == PLUS){
        // addl	$90, %eax
        sprintf(operatorString, "addl");
    }
    else if(operatorRoot->attribute.opval == MINUS){
	    // subl	$90, %eax
        sprintf(operatorString, "subl");
    }
    else if(operatorRoot->attribute.opval == STAR){
        // imull $90, %eax, %eax
        sprintf(operatorString, "imull");
    }
    else if(operatorRoot->attribute.opval == SLASH){
        sprintf(operatorString, "idivl");
    }
    else{
        fprintf(stderr, "FUCK\n");
        fprintf(stderr, "operatorRoot->type %d\n", operatorRoot->type);
        fprintf(stderr, "operatorRoot->attribute.opval %d\n", operatorRoot->attribute.opval);

        assert(0);
    }
}

void writeOperatorCode(FILE* outFile, scope_t* topScope, tree_t* operatorRoot, char* arg1, RegisterStack* reg){
    if(operatorRoot->attribute.opval == SLASH){            
        // Move name to temp register
        char tempLocation[12];
        getOffsetString(topScope->tempsAddress, tempLocation);
        genMovlCode(outFile, arg1, "%eax");
        genMovlCode(outFile, "%eax", tempLocation);
        
        genMovlCode(outFile, reg->registerName, "%eax");
        fputs("\tcltd\n", outFile);
        
        fputs("\tidivl\t", outFile);
        fputs(tempLocation, outFile);
        fputs("\n", outFile);
        genMovlCode(outFile, "%eax", reg->registerName);
    }
    else{
        char operatorString[12];
        getOperatorString(operatorRoot, operatorString);

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
    Tree is assumed to be already labeled.
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

void labelTree(tree_t* root){
    // For now, assume no functions or NOT
    if(root == NULL){
        assert(0);
        return;
    }
    // Case where root is leaf. Should only happen when no operators.
    if(isLeaf(root)){
        fprintf(stderr, "%d\n", root->type);
        root->label = 1;
        return;
    }
    if(root->type == NOT){
        labelTree(root->leftChild);
        root->label = root->leftChild->label;
    }
    else if(root->type == FUNCTION_CALL){
        assert(0);
    }
    else if(root->type == ARRAY_ACCESS){
        assert(0);
    }
    else{
        // Handle left child.
        if(hasLeftLeaf(root)){
            fprintf(stderr, "leftleaf\n", root->type);
            root->leftChild->label = 1;
        }
        else{
            fprintf(stderr, "NONleftleaf\n", root->type);
            labelTree(root->leftChild);
        }
        // Handle right child.
        if(hasRightLeaf(root)){
            fprintf(stderr, "rightleaf\n", root->type);
            root->rightChild->label = 0;
        }
        else{
            fprintf(stderr, "NONrightleaf\n", root->type);
            labelTree(root->rightChild);
        }

        fprintf(stderr, "FUCK: %d\n\n", root->attribute.ival);
        
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