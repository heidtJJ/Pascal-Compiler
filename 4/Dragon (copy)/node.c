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

/* Helpers */
node_t* node_search(node_t* top, char* name){
    node_t* cur = top;

    while(cur != NULL){
        if(!strcmp(top->name, name)){
            // Found match.
            return cur;
        }
        cur = cur->next;
    }
}

node_t* node_insert(node_t* top, char* name){
    node_t* newTop = mknode(name);
    newTop->next = top;
    return newTop;
}