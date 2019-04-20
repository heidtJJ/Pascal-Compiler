#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "node.h"
typedef struct tree_s tree_t;
#include "treeList.h"
#include "y.tab.h"

extern int yyerror( char*);

/* Constructor */

node_t* insertVarNode(node_t* top, int type, char* name){    
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    assert(newNode != NULL);

    newNode->nodeType = VAR;
    newNode->data.varInfo.type = type;
    newNode->data.varInfo.isArray = NOT_ARRAY;
    
    if(name != NULL){
        newNode->name = strdup(name);
    }
    else{
        newNode->name = NULL;
    }
    newNode->next = top;
    return newNode;
}

node_t* insertArrayNode(node_t* top, int type, char* name, int start, int end){
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    assert(newNode != NULL);

    newNode->nodeType = VAR;
    newNode->data.varInfo.type = type;
    newNode->data.varInfo.isArray = IS_ARRAY;

    if(name != NULL){
        newNode->name = strdup(name);
    }
    else{
        newNode->name = NULL;
    }
    newNode->data.varInfo.start = start;
    newNode->data.varInfo.end = end;
   
    newNode->next = top;
    return newNode;
}

node_t* insertProcedureNode(node_t* top, char* name, node_t* arguments){
    assert(name != NULL);
    
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    assert(newNode != NULL);

    newNode->nodeType = PROCEDURE;
    fprintf(stderr, "FUUFUUFFUFU\n\n\n");
    newNode->data.procedureInfo.arguments = arguments;
    newNode->data.procedureInfo.hasSideEffects = 0;
    if(name != NULL){
        newNode->name = strdup(name);
    }
    else{
        newNode->name = NULL;
    }
   
    newNode->next = top;
    return newNode;
}

node_t* insertFunctionNode(node_t* top, int returnType, char* name, node_t* arguments){
    assert(name != NULL);
    
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    assert(newNode != NULL);

    newNode->nodeType = FUNCTION;
    newNode->data.functionInfo.returnType = returnType;
    newNode->data.functionInfo.arguments = arguments;
    if(name != NULL){
        newNode->name = strdup(name);
    }
    else{
        newNode->name = NULL;
    }
   
    newNode->next = top;
    return newNode;
}

/* Destructor */
void free_list(node_t* top){
    if(top == NULL){
        return;
    }
    //fprintf(stderr, "freeing %X %X %d %s\n", top, top->next, top->nodeType, top->name);

    free_list(top->next);

    if(top->name != NULL){
        free(top->name);
    }
    else if(top->nodeType == FUNCTION){
        free_list(top->data.functionInfo.arguments);
    }
    else if(top->nodeType == PROCEDURE){
        free_list(top->data.procedureInfo.arguments);
    }
    
    free(top);
}

/* Helpers */
node_t* node_search(node_t* top, char* name){
    node_t* cur = top;

    while(cur != NULL){
        if(!strcmp(cur->name, name)){
            // Found match.
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

node_t* getBottom(node_t* top){
    if(top == NULL){
        return NULL;
    }
    if(top->next == NULL){
        return top;
    }
    else{
        return getBottom(top->next);
    }
}

/* Utility */
void print_list(node_t* top){
    if(top == NULL){
        fprintf(stderr, "[NULL]\n");
        return;
    }
    fprintf(stderr, "[%s]->", top->name);
    print_list(top->next);
}

void printArgumentList(node_t* top, int spaces){
    if(top == NULL){
        return;
    }
    for(int i = 0; i < spaces; ++i){
        fprintf(stderr, " ");
    }

    int argNumber = 0;
    //fprintf(stderr, "Argument #%d: name=%s type=", argNumber, top->name);
    fprintf(stderr, "Argument #%d: type=", argNumber);
    if(top->data.varInfo.isArray == NOT_ARRAY){
        switch (top->data.varInfo.type){
            case REAL:
                fprintf(stderr, "REAL");
                break;
            
            case INTEGER:
                fprintf(stderr, "INTEGER");
                break;  
            default:
                fprintf(stderr, "%d\n", top->data.varInfo.type);
                yyerror("Error in printArgumentList");
        }
    }
    else{
        switch (top->data.varInfo.type){
            case REAL:
                fprintf(stderr, "REAL_ARRAY");
                break;
            case INTEGER:
                fprintf(stderr, "INTEGER_ARRAY");
                break; 
        }
    }
    fprintf(stderr, "\n");
    printArgumentList(top->next, spaces);
}

/* DOES NOT TOUCH NEXT POINTER */
void copyNode(node_t* source, node_t* destination){
    assert(source != NULL && destination != NULL);

    char* name = NULL;
    if(source->name != NULL){
        name = strdup(source->name);
    }
    destination->name = name;
    
    if(source->nodeType == VAR){
        destination->nodeType = VAR;
        destination->data.varInfo.type = source->data.varInfo.type;
        if(source->data.varInfo.isArray == IS_ARRAY){
            int start = source->data.varInfo.start;
            int end = source->data.varInfo.end;
            destination->data.varInfo.start = start;
            destination->data.varInfo.end = end;
            destination->data.varInfo.isArray = IS_ARRAY;        
        }
        else{
            destination->data.varInfo.isArray = NOT_ARRAY;
        }
    }
    else{ /* Does not support subprograms yet */
        assert(0);
    }
}