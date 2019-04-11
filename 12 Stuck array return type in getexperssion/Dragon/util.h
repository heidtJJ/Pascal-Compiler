#ifndef UTIL_H
#define UTIL_H

#include "tree.h"
#include "node.h"
#include "scope.h"

int getExpressionType(scope_t* curScope, tree_t* exprTree);
void validateStatement(scope_t* curScope, tree_t* exprTree, int* flags);
void validateArguments(node_t* expectedArgs, node_t* actualArgs);
node_t* convertToNameList(tree_t* parameterTree);
node_t* copyArguments(node_t* oldArgs);

#endif