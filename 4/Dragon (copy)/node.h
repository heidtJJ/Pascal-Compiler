#ifndef NODE_H
#define NODE_H

/* Linked List */

typedef struct node_s{
    char* name;
    struct node_s* next;
} node_t;

/* Constructor */
node_t* mknode(char* str);

/* Helpers */
node_t* node_search(node_t* top, char* name);
node_t* node_insert(node_t* top, char* name);

#endif