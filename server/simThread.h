//
// Created by Vladimir on 8. 1. 2025.
//

#ifndef SIMTHREAD_H
#define SIMTHREAD_H
#include "simulation.h"

typedef struct simThreadData {
    int startWidth;
    int endWidth;
    tile (* tiles)[MAX_WIDTH][MAX_HEIGHT];
    simulationData *simData;
} simThreadData;

void simTheadDataInit(simThreadData *data, int startWidth, int endWidth, tile (* tiles)[MAX_WIDTH][MAX_HEIGHT], simulationData *simData);
void * simThread(void *args);
#endif //SIMTHREAD_H
