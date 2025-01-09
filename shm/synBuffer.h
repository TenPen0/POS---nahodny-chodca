//
// Created by Vladimir on 2. 1. 2025.
//

#ifndef SYNBUFFER_H
#define SYNBUFFER_H

#include <fcntl.h>
 #include <sys/stat.h>
 #include <semaphore.h>
#include "shm.h"

typedef struct synSimBuffer{
    simBuffer *buff_;
    int buff_fd_;
    sem_t *mut_pc_;
    sem_t *sem_produce_;
    sem_t *sem_consume_;
} synSimBuffer;

void syn_shm_buffer_init(shared_names *names, sem_t **mut_pc, sem_t **sem_produce, sem_t **sem_consume);
void syn_shm_buffer_destroy(shared_names *names, sem_t *mut_pc, sem_t *sem_produce, sem_t *sem_consume);

void syn_shm_sim_buffer_open(synSimBuffer *this, shared_names *names);
void syn_shm_sim_buffer_close(synSimBuffer *this);
void syn_shm_sim_buffer_push(synSimBuffer *this, const simulationState *input);
void syn_shm_sim_buffer_pop(synSimBuffer *this, simulationState *output);
bool syn_shm_sim_buffer_read_ended(synSimBuffer *this);
void syn_shm_sum_buffer_flush(synSimBuffer *this);

typedef struct synInputBuffer{
    inputBuffer *buff_;
    int buff_fd_;
    sem_t *mut_pc_;
    sem_t *sem_produce_;
    sem_t *sem_consume_;
} synInputBuffer;

void syn_shm_input_buffer_open(synInputBuffer *this, shared_names *names);
void syn_shm_input_buffer_close(synInputBuffer *this);
void syn_shm_input_buffer_push(synInputBuffer *this, const simulationMode *input);
void syn_shm_input_buffer_pop(synInputBuffer *this, simulationMode *output);
void syn_shm_input_buffer_read(synInputBuffer *this, simulationMode *input);


#endif //SYNBUFFER_H
