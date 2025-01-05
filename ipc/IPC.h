#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/time.h>
#include <sys/msg.h>

#define BUFFER_SIZE 1024 // 1 KB
#define TOTAL_BYTES 1073741824 // 1 GB (1024^3)

#ifndef IPC_H
#define IPC_H

// Data structure for shared memory
typedef struct shared_memory{
    char buffer[BUFFER_SIZE];
    int flag; // 0: parent writes data into shared memory, 1: child reads data from shared memory
} shared_memory;

// Data structure for pipe
typedef struct pipe{
    char buffer[BUFFER_SIZE];
} p;

// Data structure for message buffer
typedef struct message{
    long msg_type;
    char msg_text[BUFFER_SIZE];
} message;

// Data structure for a message queue
typedef struct message_queue{
    int flag; // 0: parent sends message to message queue, 1: child reads message from message queue
} message_queue;

#endif
