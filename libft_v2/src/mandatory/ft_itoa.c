//Special Case : 0 think of another way to right this, INT_MIN ( deal with make temp = long long= 

#include <stdio.h>
#include <stdlib.h>

// Helper function to calculate the number of digits in a number
int calculate_digits(long long n) {
    int len = 0;
    if (n == 0) {
        return 1; // Special case for 0
    }
    while (n) {
        n = n / 10;
        len++;
    }
    return len;
}

// Function to convert int to string
char *ft_itoa(int n) {
    long long num = n; // Use a larger type to avoid edge case handling
    int len = calculate_digits(num);

    // Allocate memory for the string
    char *str = (char *)malloc(len + 1);
    if (!str)
        return NULL;

    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }

    int i = len - 1; // Start filling from the last index
    if (num < 0) {
        str[0] = '-';
        num = -num;
    }

    // Convert the number to string from the last digit to the first
    while (num) {
        str[i--] = num % 10 + '0'; // Write digits from end to start
        num = num / 10;
    }

    str[len] = '\0'; // Null-terminate the string
    return str;
}

size_t strlcpy(char *restrict dst, const char *restrict src, size_t dstsize) {
    size_t offset = 0;

    // Copy the string with proper size handling
    if (dstsize > 0) {
        while (*(src + offset) != '\0' && offset < dstsize - 1) {
            *(dst + offset) = *(src + offset);
            offset++;
        }
        *(dst + offset) = '\0';
    }

    return offset;
}

int main() {
    int num = 0;
    char* str = ft_itoa(num);
    printf("string: %s\n", str);
    
    // Test strlcpy function
    char buffer[20];
    strlcpy(buffer, str, sizeof(buffer));
    printf("Copied string: %s\n", buffer);

    free(str);
    return 0;
}
