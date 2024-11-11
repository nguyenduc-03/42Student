#include <stdio.h>
#include <string.h>

// Declaration of the function to test
char *ft_strchr(const char *str, int search_char);

void run_tests() {
    struct {
        const char *input;
        int search_char;
        char *expected;
    } test_cases[] = {
        {"Hello", 'e', strchr("Hello", 'e')},   // 'e' is found at position 1
        {"", 'a', NULL},                        // Empty string, should return NULL
        {"42", '4', strchr("42", '4')},         // '4' is found at position 0
       // {"😊", '😊', strchr("😊", '😊')},         // Multibyte character, should match
        {"Test", 'z', NULL},                    // Character not found, should return NULL
    };

    for (unsigned long i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        // Get the result from ft_strchr
        char *result = ft_strchr(test_cases[i].input, test_cases[i].search_char);
        
        if (result == test_cases[i].expected) {
            printf("Test %ld passed\n", i + 1);
        } else {
            printf("Test %ld failed: got %p, expected %p\n", i + 1, (void *)result, (void *)test_cases[i].expected);
        }
    }
}

int main() {
    run_tests();
    return 0;
}
