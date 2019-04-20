#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "registerStack.h"

/* Push function */
RegisterStack* pushRegisterStr(RegisterStack* top, char* registerName){
    // Allocate space for a new register.
    RegisterStack* newTop = (RegisterStack*)malloc(sizeof(RegisterStack));
    assert(newTop != NULL);

    // Set the name and next register.
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

/* Reverse the order of a stack */
RegisterStack* reverseRegisterStack(RegisterStack* top){
    if(top == NULL){ return NULL; }
    RegisterStack* prev = NULL;
    RegisterStack* cur = top;
    RegisterStack* next = top->next;
    while(next != NULL){
        cur->next = prev;
        prev = cur;
        cur = next;
        next = next->next;
    }
    cur->next = prev;
    return cur;
}


void printRegisterStack(RegisterStack* top){
    fprintf(stderr, "Printing Register Stack:  ");
    while(top != NULL){
        fprintf(stderr, "%s -> ", top->registerName);
        top = top->next;
    }
    fprintf(stderr, "\n");
}