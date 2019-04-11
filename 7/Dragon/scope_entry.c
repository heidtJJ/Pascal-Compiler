#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "scope_entry.h"

ScopeEntry* makeVariable(char* name, int return_type){
    assert(name != NULL);
    assert(return_type == VAR || return_type == ARRAY || 
        return_type == PROCEDURE || return_type == FUNCTION );

    ScopeEntry* newVar = (ScopeEntry*)malloc(sizeof(ScopeEntry));
    assert(newVar != NULL);
    newVar->name = strdup(name);
    newVar->entry_type = VAR;
    newVar->return_type = return_type;
    return newVar;
}


ScopeEntry* makeArray(char* name, int return_type, int dimension, node_s* arguments){
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