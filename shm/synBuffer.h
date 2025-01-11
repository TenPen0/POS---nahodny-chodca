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
    simBuffer *buff;
    int buffFD;
    sem_t *mut;
    sem_t *semProduce;
    sem_t *semConsume;
} synSimBuffer;

void synShmBufferInit(sharedNames *names, sem_t **mut, sem_t **semProduce, sem_t **semConsume);
void synShmBufferDestroy(sharedNames *names, sem_t *mut, sem_t *semProduce, sem_t *semConsume);

void synShmSimBufferOpen(synSimBuffer *this, sharedNames *names);
void synShmSimBufferClose(synSimBuffer *this);
void synShmSimBufferPush(synSimBuffer *this, const simulationState *input);
void synShmSimBufferPop(synSimBuffer *this, simulationState *output);
bool synShmSimBufferReadEnded(synSimBuffer *this);
void synShmSimBufferFlush(synSimBuffer *this);

typedef struct synInputBuffer{
    inputBuffer *buff;
    int buffFD;
    sem_t *mut;
    sem_t *semProduce;
    sem_t *semConsume;
} synInputBuffer;

void synShmInputBufferOpen(synInputBuffer *this, sharedNames *names);
void synShmInputBufferClose(synInputBuffer *this);
void synShmInputBufferPush(synInputBuffer *this, const simulationMode *input);
void synShmInputBufferPop(synInputBuffer *this, simulationMode *output);
bool synShmInputBufferIsAvailable(synInputBuffer *this);
void synShmInputBufferFlush(synInputBuffer *this);


#endif //SYNBUFFER_H
