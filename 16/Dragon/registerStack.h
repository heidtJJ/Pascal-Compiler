#ifndef REGISTER_STACK_H
#define REGISTER_STACK_H

/* Stack data structure for registers. */
typedef struct RegisterStack_ {
    char* registerName;
    struct RegisterStack_* next;
} RegisterStack;

/* Push function */
RegisterStack* pushRegister(RegisterStack* top, char* registerName);
/* Pop function */
RegisterStack* popRegister(RegisterStack* top);
/* Free stack */
void freeRegisterStack(RegisterStack* top);

#endif