//
// Created by Vladimir on 2. 1. 2025.
//

#include "synBuffer.h"

#include <stdio.h>
#include <stdlib.h>

void synShmBufferInit(sharedNames *names, sem_t **mut, sem_t **semProduce, sem_t **semConsume) {
    *mut = sem_open(names->mut, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
    if (*mut == SEM_FAILED) {
        perror("Failed to create mutPC");
        exit(EXIT_FAILURE);
    }

    *semProduce = sem_open(names->semProduce, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, BUFF_SIZE);
    if (*semProduce == SEM_FAILED) {
        perror("Failed to create Produce");
        exit(EXIT_FAILURE);
    }

    *semConsume = sem_open(names->semConsume, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
    if (*semConsume == SEM_FAILED) {
        perror("Failed to create Consume");
        exit(EXIT_FAILURE);
    }

}
void synShmBufferDestroy(sharedNames *names, sem_t *mut, sem_t *semProduce, sem_t *semConsume) {
    if (mut != SEM_FAILED) {
        sem_close(mut);
        sem_unlink(names->mut);
    }
    if (semProduce != SEM_FAILED) {
        sem_close(semProduce);
        sem_unlink(names->semProduce);
    }

    if (semConsume != SEM_FAILED) {
        sem_close(semConsume);
        sem_unlink(names->semConsume);
    }
}

void synShmSimBufferOpen(synSimBuffer *this, sharedNames *names) {
    shmSimBufferOpen(names, &this->buff, &this->buffFD);

    this->mut = sem_open(names->mut, O_RDWR);
    if (this->mut == SEM_FAILED) {
        perror("Failed to open <NAME>");
        exit(EXIT_FAILURE);
    }
    this->semConsume = sem_open(names->semConsume, O_RDWR);
    if (this->semConsume == SEM_FAILED) {
        perror("Failed to open <NAME>");
        exit(EXIT_FAILURE);
    }
    this->semProduce = sem_open(names->semProduce, O_RDWR);
    if ( this->semProduce == SEM_FAILED) {
        perror("Failed to open <NAME>");
        exit(EXIT_FAILURE);
    }
}
void synShmSimBufferClose(synSimBuffer *this) {
    shmSimBufferClose(this->buffFD,this->buff);

    if (sem_close(this->mut) ==-1) {
        perror("Failed to close mutPC");
        exit(EXIT_FAILURE);
    }
    if (sem_close(this->semConsume) ==-1) {
        perror("Failed to close consume");
        exit(EXIT_FAILURE);
    }
    if (sem_close(this->semProduce) ==-1) {
        perror("Failed to close produce");
        exit(EXIT_FAILURE);
    }
}

void synShmSimBufferPush(synSimBuffer *this, const simulationState *input) {
    sem_wait(this->semProduce);
    sem_wait(this->mut);
    simBuffPush(this->buff, input);
    sem_post(this->mut);
    sem_post(this->semConsume);
}

void synShmSimBufferPop(synSimBuffer *this, simulationState *output) {
    sem_wait(this->semConsume);
    sem_wait(this->mut);
    simBuffPop(this->buff, output);
    sem_post(this->mut);
    sem_post(this->semProduce);
}

bool synShmSimBufferReadEnded(synSimBuffer *this) {
    sem_wait(this->mut);
    bool ended = simBuffReadEnded(this->buff);
    sem_post(this->mut);
    return ended;
}

void synShmSimBufferFlush(synSimBuffer *this) {

    int semVal;
    sem_getvalue(this->semConsume, &semVal);
    while (semVal > 0) {
        simulationState tmp;
        synShmSimBufferPop(this, &tmp);
        sem_getvalue(this->semConsume, &semVal);
    }
    simBuffInit(this->buff);
}

void synShmInputBufferOpen(synInputBuffer *this, sharedNames *names) {
    shmInputBufferOpen(names, &this->buff, &this->buffFD);

    this->mut = sem_open(names->mut, O_RDWR);
    if (this->mut == SEM_FAILED) {
        perror("Failed to open <NAME>");
        exit(EXIT_FAILURE);
    }
    this->semConsume = sem_open(names->semConsume, O_RDWR);
    if (this->semConsume == SEM_FAILED) {
        perror("Failed to open <NAME>");
        exit(EXIT_FAILURE);
    }
    this->semProduce = sem_open(names->semProduce, O_RDWR);
    if (this->semProduce == SEM_FAILED) {
        perror("Failed to open <NAME>");
        exit(EXIT_FAILURE);
    }

}

void synShmInputBufferClose(synInputBuffer *this) {
    shmInputBufferClose(this->buffFD,this->buff);

    if (sem_close(this->mut) ==-1) {
        perror("Failed to close mutPC");
        exit(EXIT_FAILURE);
    }
    if (sem_close(this->semConsume) ==-1) {
        perror("Failed to close consume");
        exit(EXIT_FAILURE);
    }

    if (sem_close(this->semProduce) ==-1) {
        perror("Failed to close consume");
        exit(EXIT_FAILURE);
    }
}

void synShmInputBufferPush(synInputBuffer *this, const simulationMode *input) {
    sem_wait(this->semProduce);
    sem_wait(this->mut);
    inputBuffPush(this->buff, input);
    sem_post(this->mut);
    sem_post(this->semConsume);
}

void synShmInputBufferPop(synInputBuffer *this, simulationMode *output) {
    sem_wait(this->semConsume);
    sem_wait(this->mut);
    inputBuffPop(this->buff, output);
    sem_post(this->mut);
    sem_post(this->semProduce);

}

bool synShmInputBufferIsAvailable(synInputBuffer *this) {
    sem_wait(this->mut);
    bool available = inputBufferIsAvailable(this->buff);
    sem_post(this->mut);
    return available;
}

void synShmInputBufferFlush(synInputBuffer *this) {
    int semVal;
    sem_getvalue(this->semConsume, &semVal);
    while (semVal > 0) {
        simulationMode  tmp;
        synShmInputBufferPop(this, &tmp);
        sem_getvalue(this->semConsume, &semVal);
    }
}


