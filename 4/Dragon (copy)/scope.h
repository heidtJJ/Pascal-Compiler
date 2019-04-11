#ifndef HASH_H
#define HASH_H
#include "node.h"

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
node_t* scope_search_all(node_t* top, char* name);
node_t* scope_search(node_t* top, char* name);
node_t* scope_insert(node_t* top, char* name);

#endif