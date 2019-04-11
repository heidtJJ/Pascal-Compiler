#ifndef CODE_GEN_H
#define CODE_GEN_H

#include "tree.h"

void labelTree(tree_t* root);
char* getFileName(char* programId);
void genExpression(tree_t* root, int isLeftMost);
void genCodePrintMain(FILE* outFile, char* fileName);
void genCodePrintHeader(FILE* outFile);
void genCodePrintProcBegin(FILE* outFile, char* procName);
void genCodePrintProcEnd(FILE* outFile, char* procName);
void lowerStackPointer(FILE* outFile, int offset);
/*

note to chase var in current scope

movl %ebp %ecx
movl (%ecx) %ecx

*/

#endif