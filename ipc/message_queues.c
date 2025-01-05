#include "IPC.h"

int main(){

    // ftok() generates a unique key
    // "message_queue.c": the pathname to an existing file
    // 65: a user-defined identifier (an integer between 0 and 255)
    key_t key = ftok("message_queue.c", 65);

    // msgget() creates or accesses a message queue
    // key: got from ftok()
    // 0666|IPC_CREAT is message queue's flag (shmflg), 0666 is flag permission, IPC_CREAT to create
    // Return the message queue's ID (msg_id)
    int msg_id = msgget(key, 0666|IPC_CREAT);
    if(msg_id  == -1){
        fprintf(stderr, "msgget failed!\n");
        exit(1);
    }

    message msg;
    msg.msg_type = 1;

    message_queue mq;
    mq.flag = 0;

    pid_t PID = fork();

    if(PID < 0){
        fprintf(stderr, "Failed to create child process!\n");
        exit(1);
    } else if(PID == 0){ // Child Process
        long bytes_received;
        for(bytes_received = 0; bytes_received < TOTAL_BYTES; bytes_received += BUFFER_SIZE){
            if(mq.flag == 1){
            // msgrcv() receives the message from the message queue
            // msg_id: got from msgget()
            // &msg: the pointer to message data structure (message buffer)
            // sizeof(msg.msg_text): the size of message buffer
            // msg.msg_type: type of message to be received, 
            // == 0: receives the first message in the queue
            // > 0: receives the first message of the specified type
            // < 0: receives the first message with the lowest priority
            // 0: message's flag (msg_flg) - 0 is blocking mode
            msgrcv(msg_id, &msg, sizeof(msg.msg_text), msg.msg_type, 0);
            mq.flag = 0;
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
            if(mq.flag == 0){
            fread(msg.msg_text, 1, sizeof(msg.msg_text), file_pointer);
            // msgsnd() sends the message to the message queue
            // msg_id: got from msgget()
            // &msg: the pointer to the message buffer
            // sizeof(msg.msg_text): the size of the message buffer
            // 0: message's flag (msg_flg) - 0 is blocking mode
            msgsnd(msg_id, &msg, sizeof(msg.msg_text), 0);
            mq.flag = 1;
            }
        }

        wait(NULL);

        gettimeofday(&end, NULL);
        // tv_sec is time in seconds, tv_usec is additional time in microseconds
        double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/((double) 1000000); // devided by 10^(-6) to convert from microseconds to seconds
        printf("Time taken: %.6f seconds\n", elapsed_time);

        fclose(file_pointer);

        // msgctl() destroys the message queue
        // msg_id: message queue's ID
        // IPC_RMID: command to remove (destroy) the message queue
        // NULL: a pointer to msqid_ds data structure
        msgctl(msg_id, IPC_RMID, NULL);

        printf("Parent and child processes finished!\n");
    }

    return 0;
}