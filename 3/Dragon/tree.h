#ifndef TREE_H
#define TREE_H

/* Tree type structure. */
typedef struct tree_s{
    int type; // Token type: INUM RNUM ID RELOP ADDOP MULOP NOT ..
    union {
        int ival; /* NUM */
        float rval; /* RNUM */
        int opval; /* RELOP ADDOP MULOP */
        char* sval; /* ID */
    } attribute;
    
    struct tree_s* leftChild;
    struct tree_s* rightChild;    
} tree_t;

/* Constructor */
tree_t* mktree(int type, tree_t* left, tree_t* right);

/* Auxiliary */
int tree_eval(tree_t*);
void tree_print(tree_t*);


/* Specialied constructions */
tree_t* mkid( char* );
tree_t* mkinum( int );
tree_t* mkrnum( float );
tree_t* mkop(int type, int opval, tree_t* left, tree_t* right);

#endif