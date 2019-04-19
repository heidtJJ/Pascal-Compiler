#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct tree_s tree_t;
#include "treeList.h"

/* Push function */
TreeList* insertTree(TreeList* top, tree_t* statement){
    TreeList* newTop = (TreeList*)malloc(sizeof(TreeList));
    assert(newTop != NULL);

    newTop->statementTree = statement;
    newTop->next = top;
    newTop->listLength = top == NULL ? 1 : top->listLength+1;

    return newTop;
}

/* Pop function */
TreeList* popStatement(TreeList* top){
    TreeList* newTop = top->next;
    tree_free(top->statementTree);
    free(top);
    return newTop;
}