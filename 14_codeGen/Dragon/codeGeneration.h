#ifndef CODE_GEN_H
#define CODE_GEN_H

#include "tree.h"

void labelTree(tree_t* root);
void genExpression(tree_t* root, int isLeftMost);

/*

note to chase var in current scope

movl %ebp %ecx
movl (%ecx) %ecx

*/

#endif