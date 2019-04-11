#ifndef ID_TYPES_H
#define ID_TYPES_H

typedef struct node_s node_t;

typedef struct VarInfo_{
    int type;/* INTEGER, INTEGER_ARRAY, REAL, REAL_ARRAY */
} VarInfo;

typedef struct ArrayInfo_{
    int type;/* INTEGER, REAL */
    int dimension;
} ArrayInfo;

typedef struct ProcedureInfo_{
    node_t* arguments;/* Linked List of types (integers) */
} ProcedureInfo;

typedef struct FunctionInfo_{
    int returnType;/* INTEGER or REAL */
    node_t* arguments;/* Linked List of types (integers) */
} FunctionInfo;

#endif