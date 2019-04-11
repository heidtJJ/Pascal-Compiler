#ifndef NODE_H
#define NODE_H

/* Linked List of Strings */

typedef struct node_s{
    char* name;
    struct node_s* next;
} node_t;

/* Constructor */
node_t* mknode(char* str);

/* Destructor */
void free_list(node_t*);

/* Helpers */
node_t* node_search(node_t* top, char* name);
node_t* node_insert(node_t* top, char* name);

/* Utility */
void print_list(node_t* top);

#endif