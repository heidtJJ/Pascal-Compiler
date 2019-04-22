#ifndef CODE_GEN_H
#define CODE_GEN_H

#include "tree.h"
#include "scope.h"

char* getFileName(char* programId);
void genStatement(FILE* outFile, tree_t* root, scope_t* topScope);
void genExpression(FILE* outFile, tree_t* root, scope_t* topScope, short isLeftMost);
void genCodePrintMain(FILE* outFile, char* fileName);
void genCodePrintHeader(FILE* outFile);
void genCodePrintProcBegin(FILE* outFile, scope_t* topScope);
void genCodePrintProcEnd(FILE* outFile, char* procName);
void setupRegisterStack();
void freeRegisters();
/*

note to chase var in current scope

movl %ebp %ecx
movl (%ecx) %ecx


to save registers.

	pushq	%rcx
	movq	(%rsp), %rcx


*/

#endif