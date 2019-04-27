#ifndef ID_TYPES_H
#define ID_TYPES_H

#include "treeList.h"

typedef struct node_s node_t;

typedef struct VarInfo_{
    int type;/* INTEGER, REAL */
    unsigned int isArray;/* Boolean 0 or 1 indicates whether the variable is an array or not*/
    int start;/* Used for arrays */
    int end;/* Used for arrays */
} VarInfo;

typedef struct ProcedureInfo_{
    node_t* arguments;/* Linked List of types (integers or real) */
    int hasSideEffects;
} ProcedureInfo;

typedef struct FunctionInfo_{
    int returnType;/* INTEGER or REAL */
    node_t* arguments;/* Linked List of types (integers or real) */
} FunctionInfo;

#endif