#ifndef CODE_GEN_H
#define CODE_GEN_H

#include "tree.h"
#include "scope.h"

// The main algorithm for outputting code to outFile based on *root.
short genCode(FILE *outFile, tree_t *root, scope_t *topScope, short subContainsSideEffects);

// Outputs code for the main function of a program.
void genCodePrintMain(FILE *outFile, char *fileName);

// Prints the assembly headers to outFile. Look at topHeader.
void genCodePrintHeader(FILE *outFile);

// Returns a filename from the heap which matches the programId.
char *getFileName(char *programId);
void setupRegisterStack();
void freeRegisters();

#endif