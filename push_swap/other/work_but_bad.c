#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
	int data[MAX_SIZE];
	int top;
} Stack;

// Initialize the stack to be empty.
void initStack(Stack *s) {
	s->top = -1;
}

// Check if the stack is empty.
int isEmpty(Stack *s) {
	return s->top == -1;
}

// Check if the stack is full.
int isFull(Stack *s) {
	return s->top == MAX_SIZE - 1;
}

// Push a value onto the stack.
void push(Stack *s, int value) {
	if (!isFull(s)) {
		s->data[++s->top] = value;
	}
}

// Pop a value from the stack.
int pop(Stack *s) {
	if (!isEmpty(s)) {
		return s->data[s->top--];
	}
	// Return an error value if the stack is empty.
	return -1;
}

// Peek at the top element of the stack.
int peek(Stack *s) {
	if (!isEmpty(s)) {
		return s->data[s->top];
	}
	return -1;
}

/*
   The following functions simulate the push_swap operations.
   They print the operation performed.
*/

void sa(Stack *a) {
	if (a->top > 0) {
		int tmp = a->data[a->top];
		a->data[a->top] = a->data[a->top - 1];
		a->data[a->top - 1] = tmp;
		printf("sa\n");
	}
}

void pb(Stack *a, Stack *b) {
	if (!isEmpty(a)) {
		push(b, pop(a));
		printf("pb\n");
	}
}

void pa(Stack *a, Stack *b) {
	if (!isEmpty(b)) {
		push(a, pop(b));
		printf("pa\n");
	}
}

void ra(Stack *a) {
	if (a->top > 0) {
		int first = pop(a);
		// Shift all elements up one index.
		for (int i = a->top; i >= 0; --i) {
			a->data[i + 1] = a->data[i];
		}
		a->data[0] = first;
		a->top++; // Adjust top after shifting
		printf("ra\n");
	}
}

void rra(Stack *a) {
	if (a->top > 0) {
		int last = a->data[0];
		// Shift all elements down one index.
		for (int i = 0; i < a->top; ++i) {
			a->data[i] = a->data[i + 1];
		}
		a->data[a->top] = last;
		printf("rra\n");
	}
}

/*
   Improved sort routine using an insertion sort–like method.
   We repeatedly take the top of stack A and insert it into
   the correct position in stack B. Once A is empty, we move
   the sorted numbers back to A.
   
   The operations printed (pa/pb) simulate the push_swap commands.
*/
void sort(Stack *a, Stack *b) {
	// Move each element from A to B in sorted order.
	while (!isEmpty(a)) {
		int tmp = pop(a);
		// For each element in B that is larger than tmp,
		// move it back to A.
		while (!isEmpty(b) && peek(b) > tmp) {
			push(a, pop(b));
			printf("pa\n");
		}
		push(b, tmp);
		printf("pb\n");
	}
	// Move the sorted elements back to A.
	while (!isEmpty(b)) {
		push(a, pop(b));
		printf("pa\n");
	}
}

int main(int argc, char **argv) {
	Stack a, b;
	initStack(&a);
	initStack(&b);

	// Read numbers from the command line and push them onto stack A.
	// The first command-line argument (argv[1]) will end up at the bottom,
	// and the last (argv[argc-1]) on top.
	for (int i = 1; i < argc; i++) {
		int num = atoi(argv[i]);
		push(&a, num);
	}

	// Perform the sort using the two stacks.
	sort(&a, &b);

	// Print the sorted stack A.
	// Since we built A so that the smallest element ends up on top,
	// popping the stack prints them in ascending order.
	while (!isEmpty(&a)) {
		printf("%d\n", pop(&a));
	}

	return 0;
}
