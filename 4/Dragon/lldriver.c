#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "scope.h"
#include "node.h"

int main(){

    /* Node Unit tests */
    node_t* nodeTop = mknode("topStr");
    print_list(nodeTop);
    free_list(nodeTop);

    nodeTop = mknode("NxtTop");
    print_list(nodeTop);

    nodeTop = node_insert(nodeTop, "NxtNxtTop1");
    nodeTop = node_insert(nodeTop, "NxtNxtTop2");
    nodeTop = node_insert(nodeTop, "NxtNxtTop3");
    nodeTop = node_insert(nodeTop, "NxtNxtTop4");
    nodeTop = node_insert(nodeTop, "NxtNxtTop5");
    
    node_t* searchedNode = node_search(nodeTop, "NxtNxtTop2");
    if(searchedNode){
        fprintf(stderr, "%s\n",  searchedNode->name);
    }
    
    print_list(nodeTop);
    free_list(nodeTop);
    
    fprintf(stderr, "\n\n");

    /* Scope Unit tests */
    scope_t* scopeTop = mkscope();

    scope_insert(scopeTop, "abcd1");
    scope_insert(scopeTop, "abcd2");
    scope_insert(scopeTop, "abcd3");
    scope_insert(scopeTop, "abcd4");
    scope_insert(scopeTop, "abcd5");
    scope_insert(scopeTop, "abcd6");


    scopeTop = push_scope(scopeTop);
    node_t* entry = scope_search(scopeTop, "abcd2");
    if(entry){
        fprintf(stderr, "scope_search: %s\n",  entry->name);
    }

    entry = scope_search_all(scopeTop, "abcd2");
    if(entry){
        fprintf(stderr, "scope_search_all: %s\n",  entry->name);
    }
    scope_insert(scopeTop, "abcd6");
    entry = scope_search(scopeTop, "abcd6");
    if(entry){
        fprintf(stderr, "scope_search: %s\n",  entry->name);
    }
    scopeTop = pop_scope(scopeTop);
    
    entry = scope_search(scopeTop, "abcd2");
    if(entry){
        fprintf(stderr, "scope_search: %s\n",  entry->name);
    }

    free_scope(scopeTop);
}