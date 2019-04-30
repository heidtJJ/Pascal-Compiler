#ifndef UTIL_H
#define UTIL_H

#include "tree.h"
#include "node.h"
#include "scope.h"
#include "treeList.h"

// General utilities
int max(int a, int b);
int hasNoReturnStmt(int flags);
short hasSideEffects(int flags);
int countDigits(int branchStringCounter);
void print_spaces(int num_spaces);
char *my_itoa(int num, char *str);

// Utilities for validating expression/statement trees.
short isArray(tree_t *root);
int getExpressionType(scope_t *curScope, tree_t *exprTree);
void validateStatement(scope_t *curScope, tree_t *exprTree, int *flags);
void validateArguments(scope_t *top_scope, node_t *expectedArgsList, TreeList *actualArgsList);
void findMaxNumArguments(TreeList *statementList, int *maxNumArguments);

#endif