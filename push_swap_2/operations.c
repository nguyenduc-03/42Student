#include <stdio.h>
#include "stack.h"
#include "operations.h"

void sa(t_stack *a) {
	if (a->size < 2) return;
	int temp = a->data[a->size - 1];
	a->data[a->size - 1] = a->data[a->size - 2];
	a->data[a->size - 2] = temp;
	printf("sa\n");
}

void sb(t_stack *b) {
	if (b->size < 2) return;
	int temp = b->data[b->size - 1];
	b->data[b->size - 1] = b->data[b->size - 2];
	b->data[b->size - 2] = temp;
	printf("sb\n");
}

void ss(t_stack *a, t_stack *b) {
	sa(a);
	sb(b);
	printf("ss\n");
}

void pa(t_stack *a, t_stack *b) {
	if (b->size == 0) return;
	push(a, pop(b));
	printf("pa\n");
}

void pb(t_stack *a, t_stack *b) {
	if (a->size == 0) return;
	push(b, pop(a));
	printf("pb\n");
}

void ra(t_stack *a) {
	if (a->size < 2) return;
	int temp = a->data[0];
	for (int i = 0; i < a->size - 1; i++) {
		a->data[i] = a->data[i + 1];
	}
	a->data[a->size - 1] = temp;
	printf("ra\n");
}

void rb(t_stack *b) {
	if (b->size < 2) return;
	int temp = b->data[0];
	for (int i = 0; i < b->size - 1; i++) {
		b->data[i] = b->data[i + 1];
	}
	b->data[b->size - 1] = temp;
	printf("rb\n");
}

void rr(t_stack *a, t_stack *b) {
	ra(a);
	rb(b);
	printf("rr\n");
}

void rra(t_stack *a) {
	if (a->size < 2) return;
	int temp = a->data[a->size - 1];
	for (int i = a->size - 1; i > 0; i--) {
		a->data[i] = a->data[i - 1];
	}
	a->data[0] = temp;
	printf("rra\n");
}

void rrb(t_stack *b) {
	if (b->size < 2) return;
	int temp = b->data[b->size - 1];
	for (int i = b->size - 1; i > 0; i--) {
		b->data[i] = b->data[i - 1];
	}
	b->data[0] = temp;
	printf("rrb\n");
}

void rrr(t_stack *a, t_stack *b) {
	rra(a);
	rrb(b);
	printf("rrr\n");
}