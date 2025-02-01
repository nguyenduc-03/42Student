#include <stdio.h>
#include <stdlib.h>

#define MAX_OPS 700

typedef struct s_node {
	int value;
	struct s_node *next;
} t_node;

typedef struct s_stack {
	t_node *top;
	int size;
} t_stack;

void push(t_stack *stack, int value);
int pop(t_stack *stack);
void sa(t_stack *a);
void sb(t_stack *b);
void ss(t_stack *a, t_stack *b);
void pa(t_stack *a, t_stack *b);
void pb(t_stack *a, t_stack *b);
void ra(t_stack *a);
void rb(t_stack *b);
void rr(t_stack *a, t_stack *b);
void rra(t_stack *a);
void rrb(t_stack *b);
void rrr(t_stack *a, t_stack *b);

void sort(t_stack *a, t_stack *b);

void print_stack(t_stack *s);

// Helper functions
void push(t_stack *stack, int value) {
	t_node *new_node = (t_node *)malloc(sizeof(t_node));
	new_node->value = value;
	new_node->next = stack->top;
	stack->top = new_node;
	stack->size++;
}

int pop(t_stack *stack) {
	if(stack->top == NULL) return 0; // Or handle underflow or signal error
	t_node *temp = stack->top;
	int ret = temp->value;
	stack->top = stack->top->next;
	free(temp);
	stack->size--;
	return ret;
}

void sa(t_stack *a) {
	if (a->size < 2) return;
	t_node *first = a->top;
	t_node *second = first->next;
	first->next = second->next;
	second->next = first;
	a->top = second;
}

void sb(t_stack *b) {
	if (b->size < 2) return;
	t_node *first = b->top;
	t_node *second = first->next;
	first->next = second->next;
	second->next = first;
	b->top = second;
}

void ss(t_stack *a, t_stack *b) {
	sa(a); sb(b);
}

void pa(t_stack *a, t_stack *b) {
	if (b->top == NULL) return;
	int value = pop(b);
	push(a, value);
}

void pb(t_stack *a, t_stack *b) {
	if (a->top == NULL) return;
	int value = pop(a);
	push(b, value);
}

void ra(t_stack *a) {
	if (a->size < 2) return;
	t_node *first = a->top;
	t_node *last = a->top;
	while (last->next) last = last->next;
	a->top = first->next;
	first->next = NULL;
	last->next = first;
}

void rb(t_stack *b) {
	if (b->size < 2) return;
	t_node *first = b->top;
	t_node *last = b->top;
	while (last->next) last = last->next;
	b->top = first->next;
	first->next = NULL;
	last->next = first;
}

void rr(t_stack *a, t_stack *b) {
	ra(a); rb(b);
}

void rra(t_stack *a) {
	if (a->size < 2) return;
	t_node *prev = NULL;
	t_node *curr = a->top;
	while (curr->next) {
		prev = curr;
		curr = curr->next;
	}
	prev->next = NULL;
	curr->next = a->top;
	a->top = curr;
}

void rrb(t_stack *b) {
	if (b->size < 2) return;
	t_node *prev = NULL;
	t_node *curr = b->top;
	while (curr->next) {
		prev = curr;
		curr = curr->next;
	}
	prev->next = NULL;
	curr->next = b->top;
	b->top = curr;
}

void rrr(t_stack *a, t_stack *b) {
	rra(a); rrb(b);
}

void fill_stack(t_stack *a, int arr[], int n) {
	for (int i = 0; i < n; i++) {
		push(a, arr[i]);
	}
}

void print_stack(t_stack *s) {
	t_node *current = s->top;
	while (current != NULL) {
		printf("%d ", current->value);
		current = current->next;
	}
	printf("\n");
}


void sort(t_stack *a, t_stack *b) {
	int size = a->top + 1;
	int sorted = 0;
	
	// Initial phase: Move all elements to stack B
	while (a->top > -1) {
		pb(a, b);
	}
	
	// Main sorting phase
	while (!sorted) {
		sorted = 1;
		
		// Transfer elements from B back to A in a sorted manner
		while (!isEmpty(b)) {
			int num = pop(b);
			
			if (isEmpty(a) || peek(a) >= num) {
				push(a, num);
			} else {
				sorted = 0;
				int count = 0;
				while (!isEmpty(a) && peek(a) < num) {
					pb(a, b);
					count++;
				}
				push(a, num);
				while (count > 0) {
					pa(a, b);
					count--;
				}
			}
		}
		
		// If not sorted, repeat
		if (!sorted) {
			for (int i = 0; i < size; ++i) {
				pb(a, b);
			}
		}
	}
}
int main() {
	t_stack a, b;
	a.top = NULL, a.size = 0;
	b.top = NULL, b.size = 0;
	
	// Assume you have a function to fill stack a with 100 random numbers
	int arr[100] = { // Fill this array with 100 random numbers
	  78, 55, 45, 98, 13, 12, 95, 91, 86, 34, 
	  23, 3,  24, 75, 71, 67, 54, 71, 63, 87, 
	  18, 46, 23, 22, 29, 12, 9,  57, 44, 47,
	  87, 68, 79, 57, 48, 46, 51, 60, 14, 53,
	  21, 56, 71, 88, 66, 35, 77, 19, 10, 49,
	  40, 80, 50, 94, 90, 83, 38, 39, 61, 62,
	  23, 25, 58, 52, 43, 26, 33, 82, 76, 95,
	  99, 4,  89, 85, 66, 74, 66, 33, 27, 16,
	  32, 87, 79, 73, 37, 98, 11, 17, 72, 81,
	  42, 93, 20, 41, 99, 36, 2,  59, 77, 100
	};
	
	sort(&a, &b);
	
	// Output the sorted stack
	return 0;
}