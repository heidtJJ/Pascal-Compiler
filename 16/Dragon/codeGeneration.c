#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "codeGeneration.h"
#include "statementList.h"
#include "registerStack.h"
#include "y.tab.h"

extern int yyerror( char*);

RegisterStack* registerStack = NULL;

/* Top of assembly file */
char* topHeader = "\t.text\n\t.section\t.rodata\n.LC0:\n\t.string\t\"%d\\n\"\n\t.text\n\t.globl\tmain\n\t.type\tmain, @function\n";

/* Assembly for creating functions/procedures. */
char* procedureCodeBegin = "\tpushq\t%rbp\n\tmovq\t%rsp, %rbp\n";
char* procedureCodeEnd = "\tleave\n\tret\n";
char* procedureEndInfo = "\n\t.globl\tmain\n\t.type\tmain, @function\n";

// Code for printf assembly.
char* printfEndCode = ", %esi\n\tleaq\t.LC0(%rip), %rdi\n\tmovl\t$0, %eax\n\tcall\tprintf\n";

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
	registerStack = pushRegister(NULL, "%r15");
	registerStack = pushRegister(registerStack, "%r14");
	registerStack = pushRegister(registerStack, "%r13");
	registerStack = pushRegister(registerStack, "%r12");
	registerStack = pushRegister(registerStack, "%r11");
	registerStack = pushRegister(registerStack, "%r10");
	registerStack = pushRegister(registerStack, "%r9");
	registerStack = pushRegister(registerStack, "%r8");
	registerStack = pushRegister(registerStack, "%edi");
	registerStack = pushRegister(registerStack, "%edx");
	registerStack = pushRegister(registerStack, "%ecx");
	registerStack = pushRegister(registerStack, "%ebx");
	registerStack = pushRegister(registerStack, "%eax");
}

void freeRegisters(){
    freeRegisterStack(registerStack);
}

void genCodePrintHeader(FILE* outFile){
    fputs(topHeader, outFile);
}

void lowerStackPointer(FILE* outFile, int offset){
    // Example: subq	$32, %rsp
    fputs("\tsubq\t$", outFile);
    char strOffset[8];// Could be dangerous. Rare that the offset has >8 characters though.
    fputs(my_itoa(offset, strOffset), outFile);
    fputs(", %rsp # lowering the stack pointer.\n", outFile);
}

void genCodePrintProcBegin(FILE* outFile, char* procName){
    fputs(procName, outFile);
    fputs(":\n", outFile);
    fputs(procedureCodeBegin, outFile);
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

void getOffsetString(node_t* varNode, char* offsetString){
    int frameOffset = varNode->frameOffset;
    if(frameOffset > 0){
        sprintf(offsetString, "-%d(%%rbp)", frameOffset);
    }
    else{
        sprintf(offsetString, "%d(%%rbp)", frameOffset);        
    }
}

void genStatement(FILE* outFile, tree_t* root){
    if(root == NULL){
        return;
    }
    else if(root->type == IF){

    }
    else if(root->type == ASSIGNOP){
        tree_t* exprTree = root->rightChild;
        tree_t* varTree = root->leftChild;
        assert(exprTree != NULL);
        
        labelTree(exprTree);// Setup expression tree for evaluation.
        genExpression(outFile, exprTree);// Generate code for expression.
        // Expression return value is now in top register.
        
        if(varTree->type == ID){
            node_t* idNode = varTree->attribute.nval;
            char strOffset[12];// Could be dangerous. Rare that the offset has >12 characters though.
            getOffsetString(idNode, strOffset);
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
        tree_t* exprTree = root->leftChild;
        assert(exprTree != NULL);
        labelTree(exprTree);
        genExpression(outFile, exprTree);
        // Expression return value is now in top register.
        genPrintfCode(outFile, registerStack->registerName);
        
    }
    else if(root->type == READ){
        
    }
    else{
        fprintf(stderr, "root->type %d\n", root->type);
        yyerror("root->type error in genStatement\n");
    }
}

void genExpression(FILE* outFile, tree_t* root){
    // Case where root is leaf. Should only happen when no operators.
    if(isLeaf(root)){
        if(root->type == INUM){
            char strNum[8];
            sprintf(strNum, "$%d", root->attribute.ival);
            genMovlCode(outFile, strNum, registerStack->registerName);
        }
        else if(root->type == RNUM){

        }
        else if(root->type == ID){
            node_t* idNode = root->attribute.nval;
            char strOffset[12];
            getOffsetString(idNode, strOffset);
            genMovlCode(outFile, strOffset, registerStack->registerName);
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
        root->label = 1;
        return;
    }
    // Handle left child.
    if(hasLeftLeaf(root)){
        root->leftChild->label = 1;
    }
    else{
        labelTree(root->leftChild);
    }
    // Handle right child.
    if(hasRightLeaf(root)){
        root->rightChild->label = 0;
    }
    else{
        labelTree(root->rightChild);
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