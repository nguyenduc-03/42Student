#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "stack.h"
#include "operations.h"
#include "utils.h"

// Function to print an error message and exit
void print_error(void) {
	fprintf(stderr, "Error\n");
	exit(1);
}

// Function to parse command-line arguments into stack a
t_stack *parse_input(int argc, char **argv) {
	t_stack *a = create_stack(argc - 1); // Create stack with capacity for all arguments
	if (!a)
		print_error();

	for (int i = 1; i < argc; i++) {
		char *endptr;
		long value = strtol(argv[i], &endptr, 10);

		// Check for invalid input (non-integer or out-of-range values)
		if (*endptr != '\0' || value < INT_MIN || value > INT_MAX)
			print_error();

		// Push the parsed integer onto stack a
		push(a, (int)value);
	}

	// Check for duplicates in the input
	if (!is_unique(a))
		print_error();

	return a;
}

// Sorting algorithm for small stacks (<= 5 elements)
void sort_small_stack(t_stack *a, t_stack *b) {
	while (!is_sorted(a)) {
		int size = a->size;
		if (size == 2) {
			sa(a); // Swap the two elements
		} else if (size == 3) {
			// Sort 3 elements
			if (peek(a) > a->data[a->size - 2] && peek(a) > a->data[a->size - 3]) {
				ra(a); // Rotate to bring the largest element to the bottom
			} else if (peek(a) > a->data[a->size - 2]) {
				sa(a); // Swap the top two elements
			}
			if (!is_sorted(a)) {
				ra(a); // Final rotation if needed
			}
		} else if (size == 4 || size == 5) {
			// Push smaller elements to stack b
			while (a->size > 3) {
				if (peek(a) <= a->data[a->size - 2] && peek(a) <= a->data[a->size - 3]) {
					pb(a, b); // Push smaller elements to stack b
				} else {
					ra(a); // Rotate to find smaller elements
				}
			}
			// Sort the remaining 3 elements in stack a
			sort_small_stack(a, b);
			// Push elements back from stack b to stack a
			while (!is_empty(b)) {
				pa(a, b);
			}
		}
	}
}

// Sorting algorithm for larger stacks (> 5 elements)
void sort_large_stack(t_stack *a, t_stack *b) {
	int size = a->size;

	// Divide the stack into chunks based on the median
	int chunk_size = size / 5; // Adjust chunk size for efficiency
	int chunks = 5;

	// Push elements into stack b in chunks
	for (int i = 0; i < chunks; i++) {
		int target = (i + 1) * chunk_size;
		while (a->size > target) {
			if (peek(a) <= target) {
				pb(a, b); // Push smaller elements to stack b
			} else {
				ra(a); // Rotate to find smaller elements
			}
		}
	}

	// Push elements back from stack b to stack a in sorted order
	while (!is_empty(b)) {
		pa(a, b);
	}
}

// Main function
int main(int argc, char **argv) {
	if (argc <= 1)
		return 0; // No arguments provided, do nothing

	// Parse input and initialize stacks
	t_stack *a = parse_input(argc, argv);
	t_stack *b = create_stack(a->capacity); // Stack b starts empty

	// If the stack is already sorted, exit early
	if (is_sorted(a)) {
		free_stack(a);
		free_stack(b);
		return 0;
	}

	// Choose sorting algorithm based on stack size
	if (a->size <= 5) {
		sort_small_stack(a, b);
	} else {
		sort_large_stack(a, b);
	}

	// Free resources
	free_stack(a);
	free_stack(b);

	return 0;
}