#include <stdio.h>

typedef struct s_list {
    void *content;
    struct s_list *next;
} t_list;

int main() {
    printf("Size of t_list: %zu\n", sizeof(t_list));
    return 0;
}