#ifndef HASH_H
#define HASH_H
#include "node.h"

/**
 * Scope is a hash table with a *next to another hash table. It's a hash table linked list
 */

#define TABLE_SIZE	211
#define EOS		'\0'

typedef struct scope_s {
    node_t* table[TABLE_SIZE];
    struct scope_s* next;
} scope_t;

/* Constructor */
scope_t* mkscope();
void free_scope(scope_t*);

/* Stack moves */
scope_t* push_scope(scope_t*);
scope_t* pop_scope(scope_t*);

/* Helpers */
node_t* scope_search_all(scope_t* top, char* name);
node_t* scope_search(scope_t* top, char* name);
node_t* scope_insert(scope_t* top, char* name);

void scope_print(scope_t* top);

#endif