#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "registerStack.h"

/* Push function */
RegisterStack* pushRegisterStr(RegisterStack* top, char* registerName){
    RegisterStack* newTop = (RegisterStack*)malloc(sizeof(RegisterStack));
    assert(newTop != NULL);

    newTop->registerName = strdup(registerName);
    newTop->next = top;

    return newTop;
}

RegisterStack* pushRegister(RegisterStack* top, RegisterStack* newTop){
    assert(newTop != NULL);

    newTop->next = top;

    return newTop;
}

/* Pop function */
RegisterStack* popRegister(RegisterStack** top){
    RegisterStack* poppedRegister = (*top);
    *top = (*top)->next;
    poppedRegister->next = NULL;
    return poppedRegister;
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

/* Swap top two elements on stack */
RegisterStack* swapRegisterStack(RegisterStack* top){
    if(top == NULL || top->next == NULL){
        assert(0);
    }
    RegisterStack* newTop = top->next;
    top->next = newTop->next;
    newTop->next = top;
    return newTop;
}