#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "statementList.h"
typedef struct tree_s tree_t;

/* Push function */
StatementList* insertStatement(StatementList* top, tree_t* statement){
    StatementList* newTop = (StatementList*)malloc(sizeof(StatementList));
    assert(newTop != NULL);

    newTop->statementTree = statement;
    newTop->next = top;

    return newTop;
}

/* Pop function */
StatementList* popStatement(StatementList* top){
    StatementList* newTop = top->next;
    tree_free(top->statementTree);
    free(top);
    return newTop;
}