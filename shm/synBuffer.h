//
// Created by Vladimir on 2. 1. 2025.
//

#ifndef SYNBUFFER_H
#define SYNBUFFER_H

#include <fcntl.h>
 #include <sys/stat.h>
 #include <semaphore.h>
#include "shm.h"

typedef struct synBuffer{
    buffer *buff_;
    int buff_fd_;
    sem_t *mut_pc_;
    //sem_t *sem_produce_;
    sem_t *sem_consume_;
} synBuffer;

void syn_shm_buffer_init(shared_names *names);
void syn_shm_buffer_destroy(shared_names *names);
void syn_shm_buffer_open(synBuffer *this, shared_names *names);
void syn_shm_buffer_close(synBuffer *this);
void syn_shm_buffer_push(synBuffer *this, const simulationState *input);
void syn_shm_buffer_pop(synBuffer *this, simulationState *output);


#endif //SYNBUFFER_H
