#ifndef CODE_GEN_H
#define CODE_GEN_H

#include "tree.h"
#include "scope.h"

void labelTree(tree_t* root);
char* getFileName(char* programId);
void genExpression(FILE* outFile, tree_t* root, scope_t* topScope);
void genStatement(FILE* outFile, tree_t* root, scope_t* topScope);
void genCodePrintMain(FILE* outFile, char* fileName);
void genCodePrintHeader(FILE* outFile);
void genCodePrintProcBegin(FILE* outFile, char* procName, scope_t* topScope);
void genCodePrintProcEnd(FILE* outFile, char* procName);
void lowerStackPointer(FILE* outFile, int offset);
void setupRegisterStack();
void freeRegisters();
/*

note to chase var in current scope

movl %ebp %ecx
movl (%ecx) %ecx

*/

#endif