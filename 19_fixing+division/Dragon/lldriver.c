#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "scope.h"
#include "node.h"
#include "idTypes.h"

int main(){

    /* Node Unit tests */
    char* str = "abcd";
    node_t* node = insertNameNode(NULL, str);
    return 0;
}