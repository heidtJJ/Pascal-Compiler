#ifndef REGISTER_STACK_H
#define REGISTER_STACK_H

/* Stack data structure for registers. */
typedef struct RegisterStack_ {
    char* registerName;
    struct RegisterStack_* next;
} RegisterStack;

/* Push function */
RegisterStack* pushRegisterStr(RegisterStack* top, char* registerName);
RegisterStack* pushRegister(RegisterStack* top, RegisterStack* newTop);
/* Pop function */
RegisterStack* popRegister(RegisterStack** top);
/* Free stack */
void freeRegisterStack(RegisterStack* top);
/* Swap top two elements on stack */
RegisterStack* swapRegisterStack(RegisterStack* top);

#endif