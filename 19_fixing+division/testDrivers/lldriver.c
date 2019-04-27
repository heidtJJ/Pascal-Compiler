#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "scope.h"
#include "node.h"

int main(){
        scope_t* top = NULL;
        node_t* tmp = NULL;
        int choice;
        char name[32];
        top = mkscope();
        while(1){
            fprintf(stderr, "0)push (1)pop (2)search (3)search_all (4)insert:\n");
            scanf("%d", &choice);
            switch (choice)
            {
                case 0: /* push */
                    top = push_scope(top);
                    break;
                case 1: /* pop */
                    top = pop_scope(top);
                    break;
                case 2: /* search */
                    tmp = scope_search(top, name);
                    break;
                case 3: /* search_all */
                    tmp = scope_search_all(top, name);
                    break;
                case 4: /* insert */
                    tmp = scope_insert(top, name);
                    break;
                default:
                    break;
            }
        }
}