#include "IPC.h"

int main(){

    // Create file descriptors for pipe
    // fd[2] creates 2 file descriptors for pipe
    // fd[0] is the read end of the pipe
    // fd[1] is the write end of the pipe
    int fd[2];
    if(pipe(fd) == -1){
        fprintf(stderr, "An error ocurred with opening the pipe\n");
        exit(1);
    }

    p p_var;

    pid_t PID = fork();

    if(PID < 0){
        fprintf(stderr, "Failed to create child process!\n");
        exit(1);
    } else if(PID == 0){ // Child Process
        // Close the write end of the pipe, since child process only reads data from the pipe
        close(fd[1]);
        long bytes_received;
        for(bytes_received = 0; bytes_received < TOTAL_BYTES; bytes_received += BUFFER_SIZE){
            // Read data from the pipe
            read(fd[0], p_var.buffer, sizeof(p_var.buffer));
        }
        printf("Data Transfer completeted!\n");
        printf("Child process has received fully: %ld bytes (%.6f%%)\n", bytes_received, ((double) 100 * bytes_received/TOTAL_BYTES));
        // Close the read end of the pipe, after the data is completely transferred
        close(fd[0]);
    } else if(PID > 0){ // Parent Process

        // Open the binary file
        // rb: read binary file
        FILE *file_pointer = fopen("data.bin", "rb"); 
        if(file_pointer == NULL){
        fprintf(stderr, "Failed to open file!\n");
        exit(1);
        }

        struct timeval start, end;
        gettimeofday(&start, NULL);

        // Close the read end of the pipe, since parent process only writes data to the pipe
        close(fd[0]);

        long bytes_sent;

        for(bytes_sent = 0; bytes_sent < TOTAL_BYTES; bytes_sent += BUFFER_SIZE){
            // Read data from the data.bin file and write it to the buffer
            fread(p_var.buffer, 1, sizeof(p_var.buffer), file_pointer);
            // Write data from the buffer to the pipe
            write(fd[1], p_var.buffer, sizeof(p_var.buffer));
        }

        // Close the write end of the pipe, after the data is completely written to the pipe
        close(fd[1]);

        wait(NULL);

        gettimeofday(&end, NULL);
        // tv_sec is time in seconds, tv_usec is additional time in microseconds
        double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/((double) 1000000); // devided by 10^(-6) to convert from microseconds to seconds
        printf("Time taken: %.6f seconds\n", elapsed_time);

        fclose(file_pointer);

        printf("Parent and child processes finished!\n");
    }

    return 0;

}