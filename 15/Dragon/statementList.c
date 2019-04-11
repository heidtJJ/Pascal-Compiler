#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "statementList.h"

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
    tree_free(top->next)
    free(top);
    return newTop;
}
