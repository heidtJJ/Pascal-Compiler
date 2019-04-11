#ifndef NODE_H
#define NODE_H

#include "idTypes.h"

#define NOT_ARRAY 0
#define IS_ARRAY 1

/* Linked List of Strings */
typedef struct node_s{
    int nodeType;/*  VAR, PROCEDURE, or FUNCTION */
    int frameOffset;/* ADDED 4/9 */
    char* name;
    union {
        VarInfo varInfo;
        ProcedureInfo procedureInfo;
        FunctionInfo functionInfo;
    } data;
    struct node_s* next;
} node_t;

/* Constructor */
node_t* insertVarNode(node_t* top, int type, char* name);
node_t* insertArrayNode(node_t* top, int type, char* name, int start, int end);
node_t* insertProcedureNode(node_t* top, char* name, node_t* arguments);
node_t* insertFunctionNode(node_t* top, int returnType, char* name, node_t* arguments);

/* Destructor */
void free_list(node_t*);

/* Helpers */
node_t* node_search(node_t* top, char* name);
node_t* node_insert(node_t* top, char* name);
void copyNode(node_t* source, node_t* destination);
node_t* getBottom(node_t* top);

/* Utility */
void print_list(node_t* top);
void printArgumentList(node_t* top, int spaces);

//int getType(node_t* typeNode);

#endif