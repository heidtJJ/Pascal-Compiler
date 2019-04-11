#ifndef ID_TYPES_H
#define ID_TYPES_H

typedef struct node_s node_t;

typedef struct VarInfo_{
    int type;/* INTEGER, REAL */
} VarInfo;

typedef struct ArrayInfo_{
    int type;/* INTEGER_ARRAY, REAL_ARRAY */
    int dimension;
} ArrayInfo;

typedef struct ProcedureInfo_{
    node_t* arguments;/* Linked List of types (integers or real) */
} ProcedureInfo;

typedef struct FunctionInfo_{
    int returnType;/* INTEGER or REAL */
    node_t* arguments;/* Linked List of types (integers or real) */
} FunctionInfo;

#endif