#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "codeGeneration.h"
#include "statementList.h"
#include "y.tab.h"

extern int yyerror( char*);

char* my_itoa(int num, char *str){
    if(str == NULL){
        return NULL;
    }
    sprintf(str, "%d", num);
    return str;
}

/* Top of assembly file */
char* topHeader = "\t.text\n\t.globl\tmain\n\t.type\tmain, @function\n";

/* Assembly for creating functions/procedures. */
char* procedureCodeBegin = "\tpushq\t%rbp\n\tmovq\t%rsp, %rbp\n";
char* procedureCodeEnd = "\tleave\n\tret\n";
char* procedureEndInfo = "\n\t.globl\tmain\n\t.type\tmain, @function\n";

/* Assembly for MAIN */
char* firstPartMainAsm = "main:\n\tpushq\t%rbp\n\tmovq\t%rsp, %rbp\n\tmovl\t$0, %eax\n";
// Needs "call	boo"
char* secondPartMainAsm = "\tmovl\t$0, %eax\n\tleave\n\tret\n";
char* mainInfoAsm = ".main:\n\t.size\tmain, .-main\n\t.ident\t\"GCC: (Ubuntu 8.2.0-7ubuntu1) 8.2.0\"\n\t.section\t.note.GNU-stack,\"\",@progbits\n";

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

void labelTree(tree_t* root){
    if(root == NULL){
        return;
    }
    else if(root->leftChild == NULL || root->rightChild == NULL){
        // We are at a leaf. This shouldn't happen.
        //fprintf(stderr, "root->leftChild %d   root->rightChild %d\n", root->leftChild, (int)root->rightChild);
        assert(0);
    }
    
    tree_t* leftChild = root->leftChild;
    tree_t* rightChild = root->rightChild;

    // Take care of left subtree.
    if(hasLeftLeaf(root)){
        leftChild->label = 1;
    }
    else{
        labelTree(leftChild);
    }

    // Take care of right subtree.
    if(hasRightLeaf(root)){
        rightChild->label = 0;
    }
    else{
        labelTree(rightChild);
    }
    
    // Label root node.
    if(leftChild->label == rightChild->label){
        root->label = rightChild->label+1;
    }
    else{
        root->label = leftChild->label > rightChild->label ? leftChild->label : rightChild->label;
    }
}

