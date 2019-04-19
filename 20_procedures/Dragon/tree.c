#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "tree.h"
#include "treeList.h"
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

/* Specialied constructions */
tree_t* mkid(node_t* node){
    tree_t* root = mktree(ID, NULL, NULL);
    root->attribute.nval = node;// Memory leak?
    return root;
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

tree_t* mktreeList( TreeList* treeList){
    tree_t* p = mktree(ARGS, NULL, NULL);
    p->attribute.listVal = treeList;
    return p;
}

void tree_label_print(tree_t* root){
    aux_label_print( root, 0 );
}

void aux_label_print( tree_t* root, int spaces){
     if(root == NULL) return;

    for(int i = 0; i < spaces; ++i){
        fprintf(stderr, " ");
    }
    fprintf(stderr, "[%d: %d]\n", root->label, root->type);

    aux_label_print(root->leftChild, spaces+4);
    aux_label_print(root->rightChild, spaces+4);
}

void tree_print(tree_t* root){
    aux_tree_print( root, 0 );
}

void aux_tree_print( tree_t* root, int spaces){
     if(root == NULL) return;

    for(int i = 0; i < spaces; ++i){
        fprintf(stderr, " ");
    }

    switch(root->type){
        case RELOP:
            fprintf(stderr, "[RELOP: %d]\n", root->attribute.opval);
            break;
        case ADDOP:
            fprintf(stderr, "[ADDOP: %d]\n", root->attribute.opval);
            break;    
        case MULOP:
            fprintf(stderr, "[MULOP: %d]\n", root->attribute.opval);
            break;
        case ID:
            fprintf(stderr, "[ID: %s]\n", root->attribute.nval->name);
            break;    
        case INUM:
            fprintf(stderr, "[INUM:%d]\n", root->attribute.ival);
            break;
        case RNUM:
            fprintf(stderr, "[RNUM:%f]\n", root->attribute.rval);
            break;
        case ARGS:
            fprintf(stderr, "[ARGS:]\n");
            TreeList* treeList = root->attribute.listVal;
            while(treeList != NULL){
                aux_tree_print(treeList->statementTree, spaces+4);
                treeList = treeList->next;
            }
            return;
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
        case SEMICOLON:
            fprintf(stderr, "[SEMICOLON]\n");
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
        case TYPE:
            fprintf(stderr, "[TYPE]\n");
            break;
        case FOR:
            fprintf(stderr, "[FOR]\n");
            break;
        case TO:
            fprintf(stderr, "[TO]\n");
            break; 
        case DO:
            fprintf(stderr, "[DO]\n");
            break;  
        case COMPOUND_STATEMENT:
            fprintf(stderr, "[COMPOUND_STATEMENT]\n");
            break;
        case WRITE:
            fprintf(stderr, "[WRITE]\n");
            break;  
        case READ:
            fprintf(stderr, "[READ]\n");
            break;      
        default:
        fprintf(stderr,"root->type: %d\n",root->type);
        yyerror("Error in tree_print");
    }

    aux_tree_print(root->leftChild, spaces+4);
    aux_tree_print(root->rightChild, spaces+4);
}

void tree_free(tree_t* root){
    if(root == NULL){
        return;
    }
    if(root->leftChild){
        tree_free(root->leftChild);
    }
    if(root->rightChild){
        tree_free(root->rightChild);
    }
    free(root);
}

int isLeaf(tree_t* root){
    if(root == NULL){
        return 0;
    }
    return root->leftChild == NULL && root->rightChild == NULL;
}

int hasLeftLeaf(tree_t* root){
    if(root == NULL || root->leftChild == NULL){
        return 0;
    }
    return isLeaf(root->leftChild);
}

int hasRightLeaf(tree_t* root){
    if(root == NULL || root->rightChild == NULL){
        return 0;
    }
    return isLeaf(root->rightChild);
}