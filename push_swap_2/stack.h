#ifndef STACK_H
#define STACK_H

typedef struct s_stack {
    int *data;
    int size;
    int capacity;
} t_stack;

t_stack *create_stack(int capacity);
void free_stack(t_stack *stack);
void push(t_stack *stack, int value);
int pop(t_stack *stack);
int peek(const t_stack *stack);
int is_empty(const t_stack *stack);
int is_sorted(const t_stack *stack);

#endif