//
// Created by Vladimir on 6. 1. 2025.
//

#ifndef INPUTTHREAD_H
#define INPUTTHREAD_H

#include "../shm/names.h"

typedef struct inputThreadData {
    sharedNames * inputNames;
    sharedNames * simNames;
}inputThreadData;

void * inputThread(void * args);
void inputThreadInit(inputThreadData * this, sharedNames * inputNames, sharedNames * simNames);

#endif //INPUTTHREAD_H
