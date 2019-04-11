#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "node.h"

/* Constructor */
node_t* mknode(char* str){
    assert(str != NULL);
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    assert(newNode != NULL);
    newNode->name = strdup(str);
    newNode->next = NULL;
    return newNode;
}

/* Destructor (Recursive) */
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

node_t* node_insert(node_t* top, char* name){
    node_t* newTop = mknode(name);
    newTop->next = top;
    return newTop;
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
