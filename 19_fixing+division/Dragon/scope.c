#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "scope.h"

#define FRAME_BLOCK_SIZE 16
#define INITIAL_BLOCK_OFFSET 8

/* Constructor */
scope_t* mkscope(){
    scope_t* newScope = (scope_t*) malloc(sizeof(scope_t));
    assert(newScope != NULL);
    for(int i = 0; i < TABLE_SIZE; ++i){
        newScope->table[i] = NULL;
    }
    newScope->next = NULL;
    newScope->scopeOwner = NULL;
    newScope->curScopeSize = FRAME_BLOCK_SIZE;
    newScope->scopeBlockCounter = 8;// 8 bytes are needed by gcc on stack.

    newScope->tempsAddress = -1;

    return newScope;
}

// Returns the frameOffset of the variable.
int addVariableToScope(scope_t* top, int numBytes){
    int curVariableOffset = top->curScopeSize - FRAME_BLOCK_SIZE + top->scopeBlockCounter;
    top->scopeBlockCounter += numBytes;
    if(top->scopeBlockCounter > FRAME_BLOCK_SIZE){
        top->curScopeSize += (top->scopeBlockCounter / FRAME_BLOCK_SIZE)*FRAME_BLOCK_SIZE;
        top->scopeBlockCounter = top->scopeBlockCounter % FRAME_BLOCK_SIZE;
    }
    return curVariableOffset;
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
scope_t* push_scope(scope_t* top, node_t* scopeOwner){
    scope_t* newTop = mkscope();
    newTop->scopeOwner = scopeOwner;
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
    node_t* oldTop = top->table[indexToInsert];
    return top->table[indexToInsert] = insertVarNode(oldTop, type, name); 
}

node_t* scope_insert_node(scope_t* top, node_t* newTop){
    int indexToInsert = hashpjw(newTop->name);
    node_t* oldTop = top->table[indexToInsert];
    newTop->next = oldTop;
    top->table[indexToInsert] = newTop;  
    return newTop;
}

node_t* scope_insert_array(scope_t* top, int type, char* name, int start, int end){
    int indexToInsert = hashpjw(name);
    node_t* oldTop = top->table[indexToInsert];
    return top->table[indexToInsert] = insertArrayNode(oldTop, type, name, start, end);  
}

node_t* scope_insert_procedure(scope_t* top, char* name, node_t* arguments){
    int indexToInsert = hashpjw(name);
    node_t* oldTop = top->table[indexToInsert];
    return top->table[indexToInsert] = insertProcedureNode(oldTop, name, arguments);  
}

node_t* scope_insert_function(scope_t* top, int returnType, char* name, node_t* arguments){
    int indexToInsert = hashpjw(name);
    node_t* oldTop = top->table[indexToInsert];
    return top->table[indexToInsert] = insertFunctionNode(oldTop, returnType, name, arguments);  
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
    for(int i = 0; i < TABLE_SIZE; ++i){
        if(top->table[i]){
            print_spaces(spaces);
            print_list(top->table[i]);
        }
    }
    scope_print_util(top->next, spaces+4);
}

void scope_print(scope_t* top){
    scope_print_util(top, 0);
}
