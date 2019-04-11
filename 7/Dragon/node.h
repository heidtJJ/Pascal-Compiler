#ifndef NODE_H
#define NODE_H

typedef struct scope_entry_s{
    char* name;
    int entry_type;/* VAR, ARRAY, PROCEDURE, or FUNCTION */
    int return_type;/* INTEGER or REAL; not used for PROCEDURE */
    int dimension;/* used ONLY for ARRAY */
    
    /* Linked list of var_type data; used ONLY for PROCEDURE and FUNCTION */
    node_s* arguments;
} scope_entry;

enum node_type { NAME, VAR_TYPE, SCOPE_ENTRY }; 
typedef struct node_s{
    node_type type;
    union {
        char* name; /* Regular String Linked List */
        int var_type; /* Regular Integer Linked List */
        scope_entry* scopeEntry;/* VAR, ARRAY, PROCEDURE, or FUNCTION */
    } data;
    struct node_s* next;
} node_t;

/* Constructor */
node_t* mknode_name(char* str);


/* Destructor */
void free_list(node_t*);

/* Helpers */
node_t* node_search(node_t* top, char* name);
node_t* node_insert(node_t* top, char* name);

/* Utility */
void print_list(node_t* top);

#endif