#ifndef UTIL_H
#define UTIL_H

#include "tree.h"
#include "node.h"
#include "scope.h"
#include "treeList.h"

int getExpressionType(scope_t* curScope, tree_t* exprTree);
void validateStatement(scope_t* curScope, tree_t* exprTree, int* flags);
void validateArguments(scope_t* top_scope, node_t* expectedArgsList, TreeList* actualArgsList);
node_t* convertToNameList(tree_t* parameterTree);
void findMaxNumArguments(TreeList* statementList, int* maxNumArguments);
int hasSideEffects(int flags);
int hasNoReturnStmt(int flags);

int max(int a, int b);
/*node_t* copyArguments(node_t* oldArgs);*/

#endif