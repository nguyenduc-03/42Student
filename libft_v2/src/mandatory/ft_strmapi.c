#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*Applies the function f to each character of the
string s, passing its index as the first argument
and the character itself as the second. A new
string is created (using malloc(3)) to collect the
results from the successive applications of f.
*/
char *ft_strmapi(char const *s, char (*f)(unsigned int, char)) {
    char *result;
    unsigned int i;

    if (!s || !f)
        return NULL;

    result = (char *)malloc((strlen(s) + 1) * sizeof(char));
    if (!result)
        return (NULL);

    i = 0;
    while (s[i] != '\0')
    {
        result[i] = f(i, s[i]);
        i++;
    }

    result[i] = '\0';
    return (result);
}

#include <stdio.h>
#include <ctype.h>

// Example transformation function
char transform(unsigned int index, char c) {
    if (index % 1 == 0)
        return toupper(c); // Uppercase if index is even
   
}

int main() {
    char const *input = "Hello World!";
    char *output;

    // Apply ft_strmapi with the transformation function
    output = ft_strmapi(input, transform);

    if (output) {
        printf("Transformed: %s\n", output);
        free(output); // Free the allocated memory
    } else {
        printf("Error: Memory allocation failed\n");
    }

    return 0;
}


