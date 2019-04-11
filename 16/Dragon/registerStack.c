#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "registerStack.h"

/* Push function */
RegisterStack* pushRegister(RegisterStack* top, char* registerName){
    RegisterStack* newTop = (RegisterStack*)malloc(sizeof(RegisterStack));
    assert(newTop != NULL);

    newTop->registerName = strdup(registerName);
    newTop->next = top;

    return newTop;
}

/* Pop function */
RegisterStack* popRegister(RegisterStack* top){
    RegisterStack* newTop = top->next;
    free(top->registerName);
    free(top);
    return newTop;
}

/* Free stack */
void freeRegisterStack(RegisterStack* top){
    while(top != NULL){
        RegisterStack* next = top->next;
        free(top->registerName);
        free(top);
        top = next;
    }
}