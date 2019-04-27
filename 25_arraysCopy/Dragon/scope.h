#ifndef HASH_H
#define HASH_H
#include "node.h"

/*
 * Scope is a hash table with a *next to another hash table. It's a hash table linked list.
*/

#define TABLE_SIZE	211
#define EOS		'\0'

typedef struct scope_s {
    // Either a FUNCTION or PROCEDURE nodeType.
    node_t* scopeOwner;

    // The 'hash table' for this scope.
    node_t* table[TABLE_SIZE];
    
    // Used for referencing subprogram names for assembly.
    char* scopeName;

    // Measured in bytes, always a multiple of 16. Intel
    // x86 requires multiple of 16 when using scanf. 
    int curScopeSize;

    // Measured in bytes. Increase curScopeSize by 16 when 4 
    // variables (16 bytes are added to scopeBlockCounter).
    int scopeBlockCounter;

    // The starting address for temporary values/registers.
    int tempsAddress;

    // Pointer to the parent scope.
    struct scope_s* next;
} scope_t;

/* Constructor */
scope_t* mkscope();
void free_scope(scope_t*);

/* Stack moves */
scope_t* push_scope(scope_t*, node_t* scopeOwner);
scope_t* pop_scope(scope_t*);

/* Helpers */
node_t* scope_search_all(scope_t* top, char* name);
node_t* scope_search(scope_t* top, char* name);

node_t* scope_insert_type(scope_t* top, int type);
node_t* scope_insert_node(scope_t* top, node_t* nodeToInsert);
node_t* scope_insert_var(scope_t* top, int type, char* name);
node_t* scope_insert_array(scope_t* top, int type, char* name, int start, int end);
node_t* scope_insert_procedure(scope_t* top, char* name, node_t* arguments);
node_t* scope_insert_function(scope_t* top, int returnType, char* name, node_t* arguments);

int addVariableToScope(scope_t* top, int numBytes);
char* getScopeName(scope_t* newTop);

void scope_print(scope_t* top);

#endif