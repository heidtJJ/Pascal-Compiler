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
    for(int i = 0; i < TABLE_SIZE; ++i){
        free(top->table[i]);
    }
    free(top);
}

/* Stack moves */
scope_t* push_scope(scope_t* top){
    scope_t* p = mkscope();
    p->next = top;
    return p;
}

scope_t* pop_scope(scope_t* top){
    if(top != NULL) return NULL;
    scope_t* p = top->next;
    free_scope(top);
    return p;
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


node_t* scope_search_all(scope_t* top, char* name){
    return NULL;
}
node_t* scope_search(scope_t* top, char* name){
    int index = hashpjw(name);
    node_t* tmp = top->table[index];
    return node_search(tmp, name);
}
node_t* scope_insert(scope_t* top, char* name){
    int index = hashpjw(name);
    node_t* tmp = top->table[index];
    top->table[index] = node_insert(tmp, name);  
}
