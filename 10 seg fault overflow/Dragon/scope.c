#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "scope.h"


/* Constructor */
scope_t* mkscope(){
    scope_t* p = (scope_t*) malloc(sizeof(scope_t));
    assert(p != NULL);
    for(int i = 0; i < TABLE_SIZE; ++i){
        p->table[i] = NULL;
    }
    p->next = NULL;
    return p;
}

void free_scope(scope_t* top){
    if(top == NULL){
        return;
    }
    free_scope(top->next);
    for(int i = 0; i < TABLE_SIZE; ++i){
        free_list(top->table[i]);
    }
    free(top);
}

/* Stack Manipulation */
scope_t* push_scope(scope_t* top){
    scope_t* newTop = mkscope();
    newTop->next = top;
    return newTop;
}

// This function pops (frees) the top of the stack of scopes. 
scope_t* pop_scope(scope_t* top){
    assert(top != NULL);

    // Create new top scope (hash table).
    scope_t* newTop = top->next;
        
    // Set top->next to NULL because free_scope will clobber the remaining linked list.
    top->next = NULL;
    free_scope(top);
    return newTop;
}

/* Helpers */

/* ----------------------------------------------------------------------------- 
 * hashpjw
 * Peter J. Weinberger's hash function 
 * Source: Aho, Sethi, and Ullman, "Compilers", Addison-Wesley, 1986 (page 436).
 */
int hashpjw( char *s )
{
	char *p; 
	unsigned h = 0, g; 
	
	for ( p = s; *p != EOS; p++ ) 
	{ 
		h = (h << 4) + (*p); 
		if ( g = h & 0xf0000000 ) 
		{ 
			h = h ^ ( g >> 24 ); 
			h = h ^ g; 
		} 
	} 
	return h % TABLE_SIZE; 
}

node_t* scope_insert_var(scope_t* top, int type, char* name){
    int indexToInsert = hashpjw(name);
    node_t* nodeToInsert = top->table[indexToInsert];
    return top->table[indexToInsert] = insertVarNode(nodeToInsert, type, name); 
}

node_t* scope_insert_node(scope_t* top, node_t* newTop){
    int indexToInsert = hashpjw(newTop->name);
    node_t* oldTop = top->table[indexToInsert];
    newTop->next = oldTop;
    top->table[indexToInsert] = newTop;  
    return newTop;
}

node_t* scope_insert_array(scope_t* top, int type, char* name, int dimension){
    int indexToInsert = hashpjw(name);
    node_t* nodeToInsert = top->table[indexToInsert];
    return top->table[indexToInsert] = insertArrayNode(nodeToInsert, type, name, dimension);  
}

node_t* scope_insert_procedure(scope_t* top, char* name, node_t* arguments){
    int indexToInsert = hashpjw(name);
    node_t* nodeToInsert = top->table[indexToInsert];
    return top->table[indexToInsert] = insertProcedureNode(nodeToInsert, name, arguments);  
}

node_t* scope_insert_function(scope_t* top, int returnType, char* name, node_t* arguments){
    int indexToInsert = hashpjw(name);
    node_t* nodeToInsert = top->table[indexToInsert];
    return top->table[indexToInsert] = insertFunctionNode(nodeToInsert, returnType, name, arguments);  
}

// Searches in current (top) scope for a name.
node_t* scope_search(scope_t* top, char* name){
    int indexToSearch = hashpjw(name);
    node_t* nodeToSearch = top->table[indexToSearch];
    return node_search(nodeToSearch, name);
}

node_t* scope_search_all(scope_t* top, char* name){
    scope_t* curScope = top;
    node_t* curEntry;
    while(curScope != NULL){
        // Search for name in current scope.
        curEntry = scope_search(curScope, name);
        if(curEntry != NULL){
            return curEntry;
        }
        // Move to the next scope.
        curScope = curScope->next;
    }
    return NULL;
}

void print_spaces(int num_spaces){
    for(int i = 0; i < num_spaces; ++i){
        fprintf(stderr, " ");
    }
}

void scope_print_util(scope_t* top, int spaces){
    if(top == NULL) return;
    scope_print_util(top->next, spaces+4);

    for(int i = 0; i < TABLE_SIZE; ++i){
        if(top->table[i]){
            print_spaces(spaces);
            print_list(top->table[i]);
        }
    }
}

void scope_print(scope_t* top){
    scope_print_util(top, 0);
}
