#ifndef TREE_H
#define TREE_H

#include "node.h"
#include "treeList.h"

/* Tree type structure. */
typedef struct tree_s{
    int type; // Token type: INUM RNUM ID RELOP ADDOP MULOP NOT ARGS ..
    union {
        int ival; // NUM
        float rval; // RNUM 
        int opval; // RELOP ADDOP MULOP 
        node_t* nval; // ID 
        TreeList* listVal; // TreeList (used for arguments) 
    } attribute;
    int label;// Label for code generation

    struct tree_s* leftChild;
    struct tree_s* rightChild;
} tree_t;

/* Constructor */
tree_t* mktree(int type, tree_t* left, tree_t* right);

/* Destructor */
void tree_free(tree_t* root);

/* Auxiliary */
void tree_print(tree_t* root);
void tree_label_print(tree_t* root);
short isLeaf(tree_t* root);
short hasLeftLeaf(tree_t* root);
short hasRightLeaf(tree_t* root);

/* Specialied constructions */
tree_t* mkid( node_t* );
tree_t* mktreeList( TreeList* );
tree_t* mkinum( int );
tree_t* mkrnum( float );
tree_t* mkop(int type, int opval, tree_t* left, tree_t* right);

#endif