#include "stack.h"
#include "utils.h"

int is_unique(const t_stack *stack) {
    for (int i = 0; i < stack->size; i++) {
        for (int j = i + 1; j < stack->size; j++) {
            if (stack->data[i] == stack->data[j])
                return 0;
        }
    }
    return 1;
}

int is_sorted(const t_stack *stack) {
    for (int i = 0; i < stack->size - 1; i++) {
        if (stack->data[i] > stack->data[i + 1])
            return 0;
    }
    return 1;
}