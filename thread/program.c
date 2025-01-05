#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int shared_value = 0;

// Increment function
void* increment(void* arg) {
    int iterations = *(int*)arg;
    for (int i = 0; i < iterations; i++) {
        shared_value++;
    }
    return NULL;
}

// Decrement function
void* decrement(void* arg) {
    int iterations = *(int*)arg;
    for (int i = 0; i < iterations; i++) {
        shared_value--;
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    // Ensure the user provides the number of iterations
    if (argc != 2) {
        fprintf(stderr, "Missing number of iterations!\n");
        return EXIT_FAILURE;
    }

    // Parse the number of iterations
    int iterations = atoi(argv[1]);
    if (iterations <= 0) {
        fprintf(stderr, "Number of iterations must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    // Thread identifiers
    pthread_t thread1, thread2;

    // Create threads
    pthread_create(&thread1, NULL, increment, &iterations);
    pthread_create(&thread2, NULL, decrement, &iterations);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Print the final value of the shared variable
    printf("Final value of shared_value after %d: %d\n",atoi(argv[1]) ,shared_value);
//after 100000, it get very random because it take longer to finish increment
    return EXIT_SUCCESS;
}
