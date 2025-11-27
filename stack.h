#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "tree.h"

typedef address infoStack; // Info di Stack adalah address
typedef struct elmStack *adrStack;

struct elmStack{
    infoStack info;
    adrStack next;
};

struct Stack{
    adrStack top;
};

void createStack(Stack &s);
bool isEmptyStack(Stack s);
void push(Stack &s, infoStack pTree); // Buat push pointer tree ke stack
void pop(Stack &s, infoStack &pTree);

#endif // STACK_H_INCLUDED
