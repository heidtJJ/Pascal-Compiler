#ifndef STATEMENT_LIST_H
#define STATEMENT_LIST_H

typedef struct tree_s tree_t;

/* Stack data structure for statements. */
typedef struct TreeList_ {
    tree_t* statementTree;
    int listLength;
    struct TreeList_* next;
} TreeList;

/* Push function */
TreeList* insertTree(TreeList* top, tree_t* statement);
/* Pop function */
TreeList* popStatement(TreeList* top);

#endif