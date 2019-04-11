#ifndef NODE_H
#define NODE_H

#include "idTypes.h"

/* Linked List of Strings */
typedef struct node_s{
    int nodeType;/* ENTRY_NAME, ENTRY_TYPE, VAR, ARRAY, PROCEDURE, or FUNCTION */
    char* name;
    union {
        int type;/* INTEGER or REAL */
        VarInfo varInfo;
        ArrayInfo arrayInfo;
        ProcedureInfo procedureInfo;
        FunctionInfo functionInfo;
    } data;
    struct node_s* next;
} node_t;

/* Constructor */
node_t* insertTypeNode(node_t* top, int type);
node_t* insertNameNode(node_t* top, char* name);
node_t* insertVarNode(node_t* top, int type, char* name);
node_t* insertArrayNode(node_t* top, int type, char* name, int dimension);
node_t* insertProcedureNode(node_t* top, char* name, node_t* arguments);
node_t* insertFunctionNode(node_t* top, int returnType, char* name, node_t* arguments);

/* Destructor */
void free_list(node_t*);

/* Helpers */
node_t* node_search(node_t* top, char* name);
node_t* node_insert(node_t* top, char* name);

/* Utility */
void print_list(node_t* top);

#endif