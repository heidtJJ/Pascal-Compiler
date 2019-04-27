#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "scope.h"
#include "util.h"

#define FRAME_BLOCK_SIZE 16
#define INITIAL_BLOCK_OFFSET 8

/* Constructor */
scope_t* mkscope(){
    // Allocate space for a new scope.
    scope_t* newScope = (scope_t*) malloc(sizeof(scope_t));
    assert(newScope != NULL);

    // Set all of its table entries to NULL.
    for(int i = 0; i < TABLE_SIZE; ++i){
        newScope->table[i] = NULL;
    }
    // Set its attributes to NULL.
    newScope->next = NULL;
    newScope->scopeName = NULL;
    newScope->scopeOwner = NULL;

    // Initialize size of scope to FRAME_BLOCK_SIZE (16).
    newScope->curScopeSize = FRAME_BLOCK_SIZE;
    newScope->scopeBlockCounter = 8;// 8 bytes are needed by gcc on stack.
    newScope->tempsAddress = -1;

    return newScope;
}

/*
    Increases room in a scope for a new variable. Returns the 
    frameOffset of a variable. curScopeSize must always be a
    factor of 16. This is required by scanf for some weird 
    reason. I am running ubuntu 18.04 intel core i7.
*/
int addVariableToScope(scope_t* top, int numBytes){
    int curVariableOffset = top->curScopeSize - FRAME_BLOCK_SIZE + top->scopeBlockCounter;
    top->scopeBlockCounter += numBytes;
    if(top->scopeBlockCounter > FRAME_BLOCK_SIZE){
        top->curScopeSize += (top->scopeBlockCounter / FRAME_BLOCK_SIZE)*FRAME_BLOCK_SIZE;
        top->scopeBlockCounter = top->scopeBlockCounter % FRAME_BLOCK_SIZE;
    }
    return curVariableOffset;
}

/*
    Frees every node in the scope as well as 
    the scope object.
*/
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

/*
    Generate the name of a scope in the format boo_foo.
    This helps assembler code to keep unique instances of
    repeated subprogram names.
*/
char* getScopeName(scope_t* newTop){
    // Cannot generate name of empty stack.
    assert(newTop != NULL);

    // If the next node in the stack is null. Return
    // a copy of the name of the current node.
    if(newTop->next == NULL){
        return strdup(newTop->scopeOwner->name);   
    }
    else{
        // Get name of current scope owner. 
        char* curScopeOwnerName = newTop->scopeOwner->name;
        int curScopeOwnerNameLen = strlen(curScopeOwnerName);

        // Get name of the previous scope (Ex: boo_foo).
        char* lastScopeName = newTop->next->scopeName;
        int lastScopeNameLen = strlen(lastScopeName);
        int newTopScopeNameLen = curScopeOwnerNameLen + lastScopeNameLen + 1;

        // Allocate space for the scope name.
        char* newTopScopeName = (char*) malloc(sizeof(char)*newTopScopeNameLen);
        
        // Copy contents from old scope name to new scope name.
        int scopeNameIndex = 0;
        for(int i = 0; i < lastScopeNameLen; ++i){
            newTopScopeName[scopeNameIndex++] = lastScopeName[i];
        }
        // Insert a '_' to ensure uniqueness.
        newTopScopeName[scopeNameIndex++] = '_';
        // Copy contents from curScopeOwnerName to scope name.
        for(int i = 0; i < curScopeOwnerNameLen; ++i){
            newTopScopeName[scopeNameIndex++] = curScopeOwnerName[i];
        }
        return newTopScopeName;
    }
}

/* Stack Manipulation */
scope_t* push_scope(scope_t* top, node_t* scopeOwner){
    assert(scopeOwner != NULL);

    // Make a new scope.
    scope_t* newTop = mkscope();

    // Copy attributes to the created scope.
    newTop->scopeOwner = scopeOwner;
    newTop->next = top;
    newTop->scopeName = getScopeName(newTop);
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
 * ----------------------------------------------------------------------------- */
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

/**************** Scope Insertion ****************/
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

/*
    Searches in a single scope for a node with name.
*/
node_t* scope_search(scope_t* top, char* name){
    assert(top != NULL);
    int indexToSearch = hashpjw(name);
    node_t* nodeToSearch = top->table[indexToSearch];
    return node_search(nodeToSearch, name);
}

/*
    Searches in all scopes for a node with name. Returns 
    the first occurence.
*/
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

/*
    Prints all of the contents of a scope to 
    stderr. 
*/
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

/*
    Uses scope_print_util to print all of the 
    contents of a scope to stderr. 
*/
void scope_print(scope_t* top){
    scope_print_util(top, 0);
}
