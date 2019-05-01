#ifndef NODE_H
#define NODE_H

#include "idTypes.h"

#define NOT_ARRAY 0
#define IS_ARRAY 1

/* Linked List of Strings */
typedef struct node_s
{
    int nodeType;    //  VAR, PROCEDURE, or FUNCTION
    int frameOffset; // Used to keep track of this variable in its scope.
    char *name;      // Used for referencing this node in a scope.
    union {
        VarInfo varInfo;
        ProcedureInfo procedureInfo;
        FunctionInfo functionInfo;
    } data;
    struct node_s *next;
} node_t;

//*********************** CONSTRUCTORS ************************
node_t *insertVarNode(node_t *top, int type, char *name);
node_t *insertArrayNode(node_t *top, int type, char *name, int start, int end);
node_t *insertProcedureNode(node_t *top, char *name, node_t *arguments);
node_t *insertFunctionNode(node_t *top, int returnType, char *name, node_t *arguments);

//*********************** DESTRUCTORS ************************
void free_list(node_t *);

/* Helpers */
node_t *node_search(node_t *top, char *name);
node_t *node_insert(node_t *top, char *name);

// Copies the attributes of one node to another. But not the *next.
void copyNode(node_t *source, node_t *destination);

// Code name is used for the name of a function in x86 code.
void setCodeName(node_t *top, char *name);
char *getCodeName(node_t *top);

// Returns 1 if the node is an array variable.
short isArrayNode(node_t *top);

// Returns bottom of linked list.
node_t *getBottom(node_t *top);

// Reverses the order of a linked list.
node_t *reverseList(node_t *top);

//**************** NODE UTILITY FUNCTIONS *****************
void print_list(node_t *top);
void printArgumentList(node_t *top, int spaces);

#endif