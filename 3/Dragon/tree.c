#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "tree.h"
#include "y.tab.h"

extern int yyerror( char*);

/* Prototype */
void aux_tree_print( tree_t*, int);

/* Constructor */
tree_t* mktree(int type, tree_t* left, tree_t* right){
    tree_t* root = (tree_t*) malloc(sizeof(tree_t));
    assert(root != NULL);// No memory can be allocated.
    root->type = type;
    root->leftChild = left;
    root->rightChild = right;
    return root;
}

void tree_print(tree_t* root){
    aux_tree_print( root, 0 );
}

/* Specialied constructions */
tree_t* mkid(char* s){
    tree_t* p = mktree(ID, NULL, NULL);
    p->attribute.sval = strdup(s);// Memory leak?
    return p;
}
tree_t* mkinum(int ival){
    tree_t* p = mktree(INUM, NULL, NULL);
    p->attribute.ival = ival;
    return p;
}

tree_t* mkrnum(float rval){
    tree_t* p = mktree(RNUM, NULL, NULL);
    p->attribute.rval = rval;
    return p;
}

tree_t* mkop(int type, int opval, tree_t* left, tree_t* right){
    tree_t* p = mktree(type, left, right);
    p->attribute.opval = opval;
    return p;
}


void aux_tree_print( tree_t* t, int spaces){
     if(t == NULL) return;

    for(int i = 0; i < spaces; ++i){
        fprintf(stderr, " ");
    }

    switch(t->type){
        case RELOP:
            fprintf(stderr, "[RELOP: %d]\n", t->attribute.opval);
            break;
        case ADDOP:
            fprintf(stderr, "[ADDOP: %d]\n", t->attribute.opval);
            break;    
        case MULOP:
            fprintf(stderr, "[MULOP: %d]\n", t->attribute.opval);
            break;
        case ID:
            fprintf(stderr, "[ID: %s]\n", t->attribute.sval);
            break;    
        case INUM:
            fprintf(stderr, "[INUM:%d]\n", t->attribute.ival);
            break;
        case RNUM:
            fprintf(stderr, "[RNUM:%f]\n", t->attribute.rval);
            break;
        case NOT:
            fprintf(stderr, "[NOT]\n");
            break;
        case ARRAY_ACCESS:
            fprintf(stderr, "[ARRAY_ACCESS]\n");
            break;
        case FUNCTION_CALL:
            fprintf(stderr, "[FUNCTION_CALL]\n");
            break;
        case COMMA:
            fprintf(stderr, "[COMMA]\n");
            break;
        case IF:
            fprintf(stderr, "[IF]\n");
            break;   
        case THEN:
            fprintf(stderr, "[THEN]\n");
            break;
        case WHILE:
            fprintf(stderr, "[WHILE]\n");
            break;
        case ASSIGNOP:
            fprintf(stderr, "[ASSIGNOP]\n");
            break;
        case PROCEDURE_CALL:
            fprintf(stderr, "[PROCEDURE_CALL]\n");
            break;      
        default:
        yyerror("Error in tree_print");
    }

    aux_tree_print(t->leftChild, spaces+4);
    aux_tree_print(t->rightChild, spaces+4);
}