#ifndef NODE_H
#define NODE_H

#include "node.h"

typedef struct ScopeEntry_s{
    char* name;
    int entry_type;/* VAR, ARRAY, PROCEDURE, or FUNCTION */
    int return_type;/* INTEGER or REAL; not used for PROCEDURE */
    int dimension;/* used ONLY for ARRAY */
    
    /* Linked list of var_type data; used ONLY for PROCEDURE and FUNCTION */
    node_s* arguments;
} ScopeEntry;


ScopeEntry* makeVariable(char* name, int return_type);
ScopeEntry* makeArray(char* name, int return_type, int dimension, node_s* arguments);

ScopeEntry* makeProcedure(char* name, int return_type, int dimension, node_s* arguments){
    assert(name != NULL);
    assert(dimension >= 0);
    assert(return_type == VAR || return_type == ARRAY || 
        return_type == PROCEDURE || return_type == FUNCTION );

    ScopeEntry* newArray = (ScopeEntry*)malloc(sizeof(ScopeEntry));
    assert(newArray != NULL);
    
    newArray->name = name;
    newArray->return_type = return_type;
    newArray->dimension = dimension;
    newArray->arguments = arguments;

    return newArray;
}


#endif