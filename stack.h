
#ifndef _STACK_H_
#define _STACK_H_

#include <stdlib.h>

struct stack {
    int top;
    unsigned capacity;
    int* array;
};
typedef struct stack stack;

stack* create_stack(unsigned capacity);
int peek(stack* s);
void push(stack* s, int item);
int pop(stack* s);

#endif
