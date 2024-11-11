#include <stdio.h>
#include <string.h>

// Declaration of the function to test
size_t ft_strlen(const char *str);

void run_tests() {
    struct {
        const char *input;
        size_t expected;
    } test_cases[] = {
        {"Hello", 0},  // Placeholder, will use strlen() to get expected
        {"", 0},
        {"42", 0},
        {"😊", 0},  // Multibyte characters
    };

    for (long unsigned int i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        // Use standard strlen for expected result
        test_cases[i].expected = strlen(test_cases[i].input);

        size_t result = ft_strlen(test_cases[i].input);
        if (result == test_cases[i].expected) {
            printf("Test %ld passed\n", i + 1);
        } else {
            printf("Test %ld failed: got %zu, expected %zu\n", i + 1, result, test_cases[i].expected);
        }
    }
}

int main() {
    run_tests();
    return 0;
}
