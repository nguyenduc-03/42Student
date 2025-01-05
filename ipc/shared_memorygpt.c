#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <wait.h>

#define SHARED_MEMORY_NAME "/my_shared_memory"
#define SHARED_MEMORY_SIZE 1024 // 1 KB
#define TOTAL_SIZE (1024 * 1024 * 1024) // 1 GB
#define DATA_READY 1
#define DATA_CONSUMED 0

int main() {
    // Create and open a shared memory object
    int shm_fd = shm_open(SHARED_MEMORY_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open failed");
        exit(EXIT_FAILURE);
    }

    // Set the size of the shared memory
    if (ftruncate(shm_fd, SHARED_MEMORY_SIZE + sizeof(int)) == -1) {
        perror("ftruncate failed");
        exit(EXIT_FAILURE);
    }

    // Map the shared memory object into the process's address space
    void *shared_memory = mmap(0, SHARED_MEMORY_SIZE + sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_memory == MAP_FAILED) {
        perror("mmap failed");
        exit(EXIT_FAILURE);
    }

    // Initialize the synchronization variable
    int *sync_var = (int *)shared_memory;
    *sync_var = DATA_CONSUMED;

    // Create a pointer to the data section in shared memory
    char *data = (char *)(shared_memory + sizeof(int));

    // Fork a child process
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // ---- Child Process (Consumer) ----
        size_t bytes_read = 0;
        while (bytes_read < TOTAL_SIZE) {
            while (*sync_var != DATA_READY); // Wait for data to be written
            bytes_read += SHARED_MEMORY_SIZE;
            *sync_var = DATA_CONSUMED; // Signal that the data has been read
        }
        exit(EXIT_SUCCESS);
    } else {
        // ---- Parent Process (Producer) ----
        // Open the input file
        FILE *file = fopen("data.bin", "rb");
        if (file == NULL) {
            perror("fopen failed");
            exit(EXIT_FAILURE);
        }

        char buffer[SHARED_MEMORY_SIZE];
        size_t bytes_sent = 0;

        // Start timing
        struct timeval start, end;
        gettimeofday(&start, NULL);

        while (bytes_sent < TOTAL_SIZE) {
            if (fread(buffer, 1, SHARED_MEMORY_SIZE, file) != SHARED_MEMORY_SIZE) {
                rewind(file); // Reset file pointer if EOF is reached
                fread(buffer, 1, SHARED_MEMORY_SIZE, file);
            }

            while (*sync_var != DATA_CONSUMED); // Wait for the consumer to read the data
            memcpy(data, buffer, SHARED_MEMORY_SIZE);
            *sync_var = DATA_READY; // Signal that new data is available
            bytes_sent += SHARED_MEMORY_SIZE;
        }

        // Wait for the child process to finish
        wait(NULL);

        // End timing
        gettimeofday(&end, NULL);
        double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;

        printf("Total bytes transferred: %zu\n", bytes_sent);
        printf("Total time taken: %.2f seconds\n", time_taken);

        // Clean up
        fclose(file);
        munmap(shared_memory, SHARED_MEMORY_SIZE + sizeof(int));
        close(shm_fd);
        shm_unlink(SHARED_MEMORY_NAME);
    }

    return 0;
}