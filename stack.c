
#include "stack.h"

#include <limits.h>
#include <stdbool.h>

stack* create_stack(unsigned capacity) {
    stack* s = (stack*)malloc(sizeof(stack));
    s->capacity = capacity;
    s->top = -1;
    s->array = (int*)malloc(sizeof(int) * s->capacity);
    return s;
}

bool is_full(stack* s) { return s->top == s->capacity - 1; }

int pop(stack* s) { return s->array[s->top--]; }

void push(stack* s, int item) {
    if (is_full(s)) return;
    s->array[++s->top] = item;
}

int peek(stack* s) { return s->array[s->top]; }
