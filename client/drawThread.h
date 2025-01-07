//
// Created by Vladimir on 6. 1. 2025.
//

#ifndef DRAWTHREAD_H
#define DRAWTHREAD_H

#include "../shm/names.h"
#include "../server/simulation.h"

typedef struct drawThreadData{
    shared_names * simNames;
} drawThreadData;

void * drawThread(void * args);
void drawBoard(int height, int width, simulationState * simState);
void drawThreadDataInit(drawThreadData * this, shared_names * simNames);

#endif //DRAWTHREAD_H
