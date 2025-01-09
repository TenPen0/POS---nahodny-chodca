//
// Created by Vladimir on 6. 1. 2025.
//

#ifndef INPUTTHREAD_H
#define INPUTTHREAD_H

#include "../shm/names.h"
#include "../shm/synBuffer.h"


typedef struct inputThreadData {
    shared_names * inputNames;
    shared_names * simNames;
}inputThreadData;

void * inputThread(void * args);
void inputThreadInit(inputThreadData * this, shared_names * inputNames, shared_names * simNames);
//void inputThreadDestroy(inputThreadData * this);

int readInt(int min, int max);
#endif //INPUTTHREAD_H
