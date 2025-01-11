//
// Created by Vladimir on 6. 1. 2025.
//

#ifndef DRAWTHREAD_H
#define DRAWTHREAD_H

#include <stdio.h>

#include "../shm/names.h"
#include "../server/simulationStructs.h"

typedef struct drawThreadData{
    sharedNames * simNames;
    simulationData * simData;
} drawThreadData;

void * drawThread(void * args);
void drawThreadDataInit(drawThreadData * this, sharedNames * simNames, simulationData * simData);
void drawBoard(simulationData * simData, simulationState * simState, void(*drawTile)(simulationState*, int, int, FILE*), FILE * file);
void drawAverageTile(simulationState * simState,int x, int y, FILE * file);
void drawProbabilityTile(simulationState * simState, int x, int y, FILE * file);

#endif //DRAWTHREAD_H
