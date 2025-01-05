#include "IPC.h"

int main(){

    // shmget(): Create shared memory segment (reserving a workspace in the system for communication)
    // IPC_PRIVATE is key: A unique identifier for the shared memory segment
    // sizeof(share_memory): Size of the shared memory segment
    // 0666|IPC_CREAT is shared memory segment's flag (shmflg), 0666 is flag permission, IPC_CREAT to create 
    // Returns the shared memory segment's ID (shm_id)
    int shm_id = shmget((key_t)IPC_PRIVATE, sizeof(shared_memory), 0666|IPC_CREAT); 
    if(shm_id == -1){
        fprintf(stderr, "shmget failed!\n");
        exit(1);
    }
    // Attach shared memory segment to a process's address space (opening the workspace to work in it)
    // 0 is read or write, SHM_RDONLY is read-only
    shared_memory* shm = (shared_memory*)shmat(shm_id, NULL, 0); 

    // Indicate that parent process can write
    shm->flag = 0;

    pid_t PID = fork();

    if(PID < 0){
        fprintf(stderr, "Failed to create child process!\n");
        exit(1);
    } else if(PID == 0){ // Child Process
        long bytes_received;
        char child_buffer[BUFFER_SIZE];
        for(bytes_received = 0; bytes_received < TOTAL_BYTES; bytes_received += BUFFER_SIZE){
            if(shm->flag == 1){
            // memcpy(): reads the data from the shared memory into the child buffer
            // child_buffer: the pointer to the memory location where the copied data will be stored
            // shm->buffer: the pointer to the memory location where the data is to be copied
            // sizeof(shm->buffer): the number of bytes to be copied
            memcpy(child_buffer, shm->buffer, sizeof(shm->buffer));
            shm->flag = 0;
            }
        }
        printf("Data Transfer completeted!\n");
        printf("Child process has received fully: %ld bytes (%.6f%%)\n", bytes_received, ((double) 100 * bytes_received/TOTAL_BYTES));
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

        long bytes_sent;
        for(bytes_sent = 0; bytes_sent < TOTAL_BYTES; bytes_sent += BUFFER_SIZE){
            if(shm->flag == 0){
            // fread(): reads the given amount of data and store (write) it into the shared memory
            // shm->buffer: the pointer to the buffer memory block (shared memory segment) where the data read will be stored
            // 1: the size of each element in bytes
            // sizeof(shm->buffer): the count of elements to be read
            // file_pointer: the pointer to the file stream (data.bin file)
            fread(shm->buffer, 1, sizeof(shm->buffer), file_pointer);
            shm->flag = 1;
            }
        }

        wait(NULL);

        gettimeofday(&end, NULL);
        // tv_sec is time in seconds, tv_usec is additional time in microseconds
        double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/((double) 1000000); // devided by 10^(-6) to convert from microseconds to seconds
        printf("Time taken: %.6f seconds\n", elapsed_time);

        fclose(file_pointer);

        // shmctl() destroys the shared memory segment
        // shm_id: share memory segment ID
        // IPC_RMID: command to remove (destroy) the share memory segment
        // NULL: a pointer to shmid_ds data structure
        shmctl(shm_id, IPC_RMID, NULL);

        printf("Parent and child processes finished!\n");
    }

    return 0;
}

/* Workflow of the parent and child process in this program:
 *
 * 1. Parent writes 1024 bytes to shared memory, and then set shm->flag = 1
 *
 * 2. Child detects shm->flag == 1, then reads data and set shm->flag = 0
 *
 * 3. Parent detects shm->flag == 0, then writes the next data and set shm->flag = 1
 *
 * 4. Repeat step 2. und 3. until 1 GB is transferred
 *
 * 5. Parent finishes its loop and move to wait(NULL)
 *
 * 6. Child finishes its loop and exits
 *
 * 7. wait(NULL) completes, and the parent records the elapsed time using gettimeofday()
 *
 * NOTICE: The parent and child process execute concurrently but are synchronized using the flag (shm->flag)
 *
 */