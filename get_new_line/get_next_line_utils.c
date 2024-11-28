#include "get_next_line.h"

// Find the length of a string
size_t gnl_strlen(const char *str) {
    size_t len = 0;
    while (str && str[len])
        len++;
    return len;
}

// Concatenate two strings
char *gnl_strjoin(char *s1, char *s2) {
    size_t len1 = gnl_strlen(s1);
    size_t len2 = gnl_strlen(s2);
    char *joined = malloc(len1 + len2 + 1);
    if (!joined) return NULL;

    for (size_t i = 0; i < len1; i++)
        joined[i] = s1[i];
    for (size_t i = 0; i < len2; i++)
        joined[len1 + i] = s2[i];
    joined[len1 + len2] = '\0';

    free(s1); // Free old s1
    return joined;
}

// Check for newline in string
int gnl_has_newline(const char *str) {
    if (!str) return 0;
    while (*str) {
        if (*str == '\n')
            return 1;
        str++;
    }
    return 0;
}

// Duplicate string up to a specified length
char *gnl_strdup(const char *src, size_t n) {
    char *dup = malloc(n + 1);
    if (!dup) return NULL;

    for (size_t i = 0; i < n; i++)
        dup[i] = src[i];
    dup[n] = '\0';
    return dup;
}
