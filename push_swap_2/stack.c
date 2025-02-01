#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

t_stack *create_stack(int capacity) {
	t_stack *stack = malloc(sizeof(t_stack));
	if (!stack)
		return NULL;
	stack->data = malloc(sizeof(int) * capacity);
	if (!stack->data) {
		free(stack);
		return NULL;
	}
	stack->size = 0;
	stack->capacity = capacity;
	return stack;
}

void free_stack(t_stack *stack) {
	if (stack) {
		free(stack->data);
		free(stack);
	}
}

void push(t_stack *stack, int value) {
	if (stack->size < stack->capacity) {
		stack->data[stack->size++] = value;
	}
}

int pop(t_stack *stack) {
	if (stack->size > 0) {
		return stack->data[--stack->size];
	}
	return 0; // Error case
}

int peek(const t_stack *stack) {
	if (stack->size > 0) {
		return stack->data[stack->size - 1];
	}
	return 0; // Error case
}

int is_empty(const t_stack *stack) {
	return stack->size == 0;
}