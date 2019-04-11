#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "node.h"
typedef struct tree_s tree_t;
#include "y.tab.h"

/* Constructor */
node_t* insertNameNode(node_t* top, char* name){
    assert(name != NULL);
    
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    assert(newNode != NULL);

    newNode->nodeType = ENTRY_NAME;
    newNode->name = strdup(name);
   
    newNode->next = top;
    return newNode;
}

node_t* insertTypeNode(node_t* top, int type){
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    assert(newNode != NULL);

    newNode->nodeType = ENTRY_TYPE;
    newNode->data.type = type;
   
    newNode->next = top;
    return newNode;
}

node_t* insertVarNode(node_t* top, int type, char* name){
    assert(name != NULL);
    
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    assert(newNode != NULL);

    newNode->nodeType = VAR;
    newNode->data.varInfo.type = type;
    newNode->name = strdup(name);
   
    newNode->next = top;
    return newNode;
}

node_t* insertArrayNode(node_t* top, int type, char* name, int dimension){
    assert(name != NULL);
    
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    assert(newNode != NULL);

    newNode->data.arrayInfo.type = type;
    newNode->name = strdup(name);
    newNode->data.arrayInfo.dimension = dimension;
    newNode->nodeType = ARRAY;
   
    newNode->next = top;
    return newNode;
}

node_t* insertProcedureNode(node_t* top, char* name, node_t* arguments){
    assert(name != NULL);
    
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    assert(newNode != NULL);

    newNode->data.procedureInfo.arguments = arguments;
    newNode->name = strdup(name);
    newNode->nodeType = PROCEDURE;
   
    newNode->next = top;
    return newNode;
}

node_t* insertFunctionNode(node_t* top, int returnType, char* name, node_t* arguments){
    assert(name != NULL);
    
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    assert(newNode != NULL);

    newNode->data.functionInfo.returnType = returnType;
    newNode->name = strdup(name);
    newNode->data.functionInfo.arguments = arguments;
    newNode->nodeType = FUNCTION;
   
    newNode->next = top;
    return newNode;
}

/* Destructor */
void free_list(node_t* top){
    if(top == NULL){
        return;
    }
    free_list(top->next);
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
/*
node_t* node_insert(node_t* top, char* name){
    node_t* newTop = mknode(name);
    newTop->next = top;
    return newTop;
}
*/

/* Utility */
void print_list(node_t* top){
    if(top == NULL){
        fprintf(stderr, "[NULL]\n");
        return;
    }
    fprintf(stderr, "[%s]->", top->name);
    print_list(top->next);
}
