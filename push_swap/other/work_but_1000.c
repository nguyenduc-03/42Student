#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// We define a stack structure where index 0 is the top.
typedef struct {
	int data[MAX_SIZE];
	int size; // number of elements currently in the stack.
} Stack;

//----------------------
// Stack Utility Functions
//----------------------

// Initialize an empty stack.
void initStack(Stack *s) {
	s->size = 0;
}

// Returns 1 if the stack is empty.
int isEmpty(Stack *s) {
	return s->size == 0;
}

// Push a value onto the stack (inserting at index 0).
void push(Stack *s, int value) {
	if (s->size < MAX_SIZE) {
		// Shift existing elements one position down.
		for (int i = s->size; i > 0; i--) {
			s->data[i] = s->data[i-1];
		}
		s->data[0] = value;
		s->size++;
	}
}

// Pop the top value from the stack (remove and return element at index 0).
int pop(Stack *s) {
	if (!isEmpty(s)) {
		int value = s->data[0];
		// Shift the rest of the elements upward.
		for (int i = 0; i < s->size - 1; i++) {
			s->data[i] = s->data[i+1];
		}
		s->size--;
		return value;
	}
	return -1; // Error value if empty.
}

// Return the top element without removing it.
int peek(Stack *s) {
	if (!isEmpty(s))
		return s->data[0];
	return -1;
}

//----------------------
// Push_swap Operations (each prints the operation name)
//----------------------

// Swap the first two elements of stack A.
void sa(Stack *a) {
	if (a->size >= 2) {
		int tmp = a->data[0];
		a->data[0] = a->data[1];
		a->data[1] = tmp;
		printf("sa\n");
	}
}

// Push the top element from stack A to stack B.
void pb(Stack *a, Stack *b) {
	if (!isEmpty(a)) {
		int value = pop(a);
		push(b, value);
		printf("pb\n");
	}
}

// Push the top element from stack B to stack A.
void pa(Stack *a, Stack *b) {
	if (!isEmpty(b)) {
		int value = pop(b);
		push(a, value);
		printf("pa\n");
	}
}

// Rotate stack A upward (the top element becomes the bottom).
void ra(Stack *a) {
	if (a->size > 1) {
		int topVal = pop(a); // removes the element at index 0.
		// Append the removed element at the bottom.
		a->data[a->size] = topVal;
		a->size++;
		printf("ra\n");
	}
}

// Rotate stack B upward.
void rb(Stack *b) {
	if (b->size > 1) {
		int topVal = pop(b);
		b->data[b->size] = topVal;
		b->size++;
		printf("rb\n");
	}
}

// Reverse rotate stack A (the bottom element becomes the top).
void rra(Stack *a) {
	if (a->size > 1) {
		int bottom = a->data[a->size - 1];
		// Shift all elements down by one.
		for (int i = a->size - 1; i > 0; i--) {
			a->data[i] = a->data[i-1];
		}
		a->data[0] = bottom;
		printf("rra\n");
	}
}

// Reverse rotate stack B.
void rrb(Stack *b) {
	if (b->size > 1) {
		int bottom = b->data[b->size - 1];
		for (int i = b->size - 1; i > 0; i--) {
			b->data[i] = b->data[i-1];
		}
		b->data[0] = bottom;
		printf("rrb\n");
	}
}

//----------------------
// Normalization Helpers
//----------------------

// Copy the array into sorted (using bubble sort since n is small)
void copy_and_sort(int *arr, int size, int *sorted) {
	for (int i = 0; i < size; i++)
		sorted[i] = arr[i];
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (sorted[j] > sorted[j+1]) {
				int tmp = sorted[j];
				sorted[j] = sorted[j+1];
				sorted[j+1] = tmp;
			}
		}
	}
}

// Normalize the array: replace each element with its index in the sorted order.
void normalize(int *arr, int size) {
	int *sorted = malloc(sizeof(int) * size);
	if (!sorted) exit(1);
	copy_and_sort(arr, size, sorted);
	for (int i = 0; i < size; i++) {
		// Find arr[i] in the sorted array.
		for (int j = 0; j < size; j++) {
			if (arr[i] == sorted[j]) {
				arr[i] = j;
				break;
			}
		}
	}
	free(sorted);
}

//----------------------
// Radix Sort Algorithm Using Push_swap Operations
//----------------------
//
// We first find the number of bits needed (max_bits) for numbers 0..(n-1).
// Then for each bit, we iterate over all elements in A:
//   - If the current bit is 1, we rotate A (ra).
//   - If it is 0, we push it to B (pb).
// Then we push everything back from B to A (pa).
// This yields a sorted stack (with the smallest number at the top).
void radix_sort(Stack *a, Stack *b, int size) {
	int max_num = size - 1;  // since numbers have been normalized to 0..size-1.
	int max_bits = 0;
	while ((max_num >> max_bits) != 0)
		max_bits++;
	
	for (int i = 0; i < max_bits; i++) {
		int n = a->size;
		for (int j = 0; j < n; j++) {
			int num = peek(a);
			// If the i-th bit is 1, rotate A.
			if (((num >> i) & 1) == 1)
				ra(a);
			else
				pb(a, b);
		}
		// Bring all numbers back from B to A.
		while (!isEmpty(b))
			pa(a, b);
	}
}

//----------------------
// Main
//----------------------
int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s number1 number2 ...\n", argv[0]);
		return 1;
	}
	int size = argc - 1;
	if (size > MAX_SIZE) {
		fprintf(stderr, "Error: Maximum %d numbers allowed.\n", MAX_SIZE);
		return 1;
	}
	int arr[MAX_SIZE];
	for (int i = 0; i < size; i++) {
		arr[i] = atoi(argv[i+1]);
	}
	
	// Normalize the numbers.
	normalize(arr, size);
	
	Stack a, b;
	initStack(&a);
	initStack(&b);
	
	// Push the normalized numbers onto stack A.
	// (The first command–line number becomes the bottom and the last becomes the top.)
	// Since our push() inserts at the top (index 0), we push the numbers in reverse.
	for (int i = size - 1; i >= 0; i--) {
		push(&a, arr[i]);
	}
	
	// Perform the radix sort.
	radix_sort(&a, &b, size);
	
	// (Optional) Print the final sorted stack.
	// The stack will be printed from top (index 0) to bottom.
/*	for (int i = 0; i < a.size; i++) {
		printf("%d\n", a.data[i]);
	}*/
	
	return 0;
}
