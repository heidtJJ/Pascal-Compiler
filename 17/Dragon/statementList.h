#ifndef STATEMENT_LIST_H
#define STATEMENT_LIST_H

#include "tree.h"

/* Stack data structure for statements. */
typedef struct StatementList_ {
    tree_t* statementTree;
    struct StatementList_* next;
} StatementList;

/* Push function */
StatementList* insertStatement(StatementList* top, tree_t* statement);
/* Pop function */
StatementList* popStatement(StatementList* top);

#endif