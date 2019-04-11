#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "codeGeneration.h"
#include "y.tab.h"

extern int yyerror( char*);

/* Assembly for MAIN */
char* topHeader = "\t.text\n\t.globl\tmain\n\t.type\tmain, @function\n";
char* firstPartMainAsm = "main:\n\tpushq\t%rbp\n\tmovq\t%rsp, %rbp\n\tmovl\t$0, %eax\n";
// Needs "call	boo"
char* secondPartMainAsm = "\tmovl\t$0, %eax\n\tpopq\t%rbp\n\tret\n";
char* mainInfoAsm = ".main:\n\t.size\tmain, .-main\n\t.ident\t\"GCC: (Ubuntu 8.2.0-7ubuntu1) 8.2.0\"\n\t.section\t.note.GNU-stack,\"\",@progbits\n";

/* Assembly for creating functions. */
char* procedureBegin = "\tpushq\t%rbp\n\tmovq\t%rsp, %rbp\n";
char* procedureEnd = "\tpopq\t%rbp\n\tret\n";

void genCodePrintProcBegin(FILE* outFile, char* procName){
    fputs(procName, outFile);
    fputs("\n\tpushq\t%rbp\n\tmovq\t%rsp, %rbp\n", outFile);
    fputs(topHeader, outFile);
    fputs(procedureBegin, outFile);
}

void genCodePrintProcEnd(FILE* outFile){
    fputs(topHeader, outFile);
    fputs(procedureEnd, outFile);
}

void genCodePrintHeader(FILE* outFile){
    fputs(topHeader, outFile);
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
        root->label = max(leftChild->label, rightChild->label);
    }
}

