#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "node.h"
typedef struct tree_s tree_t;
#include "y.tab.h"

extern int yyerror( char*);

/* Constructor */

/* 
    Used primarily to take advantage of data.type.
    The nodeType is set to ARGUMENT_TYPE.
*/
node_t* insertTypeNode(node_t* top, int type){
    fprintf(stderr, "node.c line 19 before malloc\n");
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    fprintf(stderr, "node.c line 21 after malloc\n");
    assert(newNode != NULL);

    newNode->nodeType = ARGUMENT_TYPE;
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
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    assert(newNode != NULL);

    newNode->data.arrayInfo.type = type;
    if(name != NULL){
        newNode->name = strdup(name);
    }
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


int getType(node_t* typeNode){
    if(typeNode == NULL){
        yyerror("Error in getType");
    }
    if(typeNode->nodeType == ARGUMENT_TYPE){
        return typeNode->data.type;
    }
    else{/* typeNode->nodeType == ARRAY */
        if(typeNode->data.type == INTEGER){
            return INTEGER_ARRAY;                    
        }
        else{
            return REAL_ARRAY;
        }
    }    
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
    switch (top->data.varInfo.type){
        case REAL:
            fprintf(stderr, "REAL");
            break;
        case REAL_ARRAY:
            fprintf(stderr, "REAL_ARRAY");
            break;
        case INTEGER:
            fprintf(stderr, "INTEGER");
            break;  
        case INTEGER_ARRAY:
            fprintf(stderr, "INTEGER_ARRAY");
            break;    
        default:
            yyerror("Error in printArgumentList");
    }
    fprintf(stderr, "\n");
    printArgumentList(top->next, spaces);
}
