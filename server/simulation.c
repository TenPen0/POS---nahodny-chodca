//
// Created by Vladimir on 10. 1. 2025.
//

#include "simulation.h"

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "simThread.h"


void moveUp(coordinates * initialCoor, coordinates * currentCoor, tile (* tiles)[MAX_WIDTH][MAX_HEIGHT]) {
    if (currentCoor->y > 0) {
        currentCoor->y--;
    }
    (*tiles)[initialCoor->x][initialCoor->y].steps++;
}

void moveDown(coordinates * initialCoor, coordinates * currentCoor, tile (* tiles)[MAX_WIDTH][MAX_HEIGHT], simulationData* simData) {
    if (currentCoor->y < simData->height - 1) {
        currentCoor->y++;
    }
    (*tiles)[initialCoor->x][initialCoor->y].steps++;
}

void moveLeft(coordinates * initialCoor, coordinates * currentCoor, tile (* tiles)[MAX_WIDTH][MAX_HEIGHT]) {
    if (currentCoor->x > 0) {
        currentCoor->x--;
    }
    (*tiles)[initialCoor->x][initialCoor->y].steps++;
}

void moveRight(coordinates * initialCoor, coordinates * currentCoor, tile (* tiles)[MAX_WIDTH][MAX_HEIGHT], simulationData* simData) {
    if (currentCoor->x < simData->width - 1) {
        currentCoor->x++;
    }
    (*tiles)[initialCoor->x][initialCoor->y].steps++;
}


bool checkCenter(simulationData * simData, coordinates * currentCoor) {
    if (currentCoor->y == simData->centerY && currentCoor->x == simData->centerX) {
        return true;
    } else {
        return false;
    }
}
void runTileSummary(simulationData * simData, coordinates *initialCoor, tile (* tiles)[MAX_WIDTH][MAX_HEIGHT]) {
    coordinates currentCoor = {initialCoor->x, initialCoor->y};
    for (int i = 0; i < simData->maxSteps; i++) {
        int direction = rand() % 100;
        if (direction < simData->up) {
            moveUp(initialCoor, &currentCoor, tiles);
        } else if (direction < simData->down) {
            moveDown(initialCoor, &currentCoor, tiles, simData);
        } else if (direction < simData->left) {
            moveLeft(initialCoor, &currentCoor, tiles);
        } else if (direction < simData->right) {
            moveRight(initialCoor, &currentCoor, tiles, simData);
        }

        if (checkCenter(simData, &currentCoor)) {
            (*tiles)[initialCoor->x][initialCoor->y].successfulls++;
            return;
        }
    }
    //nedosiel do ciela
    (*tiles)[initialCoor->x][initialCoor->y].steps -= simData->maxSteps;
}

void runTileInteractive(simulationData * simData, simulationState * simState, coordinates *initialCoor, synSimBuffer * simBuff, synInputBuffer * inputBuff) {
    simState->currentCoor = *initialCoor;
    for (int i = 0; i < simData->maxSteps; i++) {
        if (synShmInputBufferIsAvailable(inputBuff)) {
            synShmInputBufferPop(inputBuff, &simState->mode);
        }
        int direction = rand() % 100;
        if (direction < simData->up) {
            moveUp(initialCoor, &simState->currentCoor, &simState->tiles);
        } else if (direction < simData->down) {
            moveDown(initialCoor, &simState->currentCoor, &simState->tiles, simData);
        } else if (direction < simData->left) {
            moveLeft(initialCoor, &simState->currentCoor, &simState->tiles);
        } else if (direction < simData->right) {
            moveRight(initialCoor, &simState->currentCoor, &simState->tiles, simData);
        }

        if (synShmInputBufferIsAvailable(inputBuff)) {
            synShmInputBufferPop(inputBuff, &simState->mode);
        }
        if (simState->mode == interactive) {
            if (checkCenter(simData, &simState->currentCoor)) {
                simState->tiles[initialCoor->x][initialCoor->y].successfulls++;
                synShmSimBufferPush(simBuff, simState);
                return;
            }
            synShmSimBufferPush(simBuff, simState);
            usleep(400000);
        } else {
            if (checkCenter(simData, &simState->currentCoor)) {
                simState->tiles[initialCoor->x][initialCoor->y].successfulls++;
                return;
            }
        }
    }
    //nedosiel do ciela
    simState->tiles[initialCoor->x][initialCoor->y].steps -= simData->maxSteps;
}

void runReplicationSummary(simulationData * simData, simulationState * simState, synSimBuffer * simBuff, synInputBuffer * inputBuff) {
    int threads = (simData->width / 5) + 1;
    int widthPerThread = simData->width / threads;
    pthread_t id[threads];
    simThreadData sData[threads];
    for (int i = 0; i < threads; i++) {
        int startColumn = widthPerThread * i;
        int endColumn = widthPerThread * (i + 1) - 1;
        if (i == (threads - 1)) {
            endColumn = simData->width-1;
        }
        simTheadDataInit(&sData[i],startColumn, endColumn, &simState->tiles, simData);
        pthread_create(&id[i], NULL, simThread, &sData[i]);
    }
    for (int i = 0; i < threads; i++) {
        pthread_join(id[i], NULL);
    }
    synShmSimBufferPush(simBuff, simState);
    usleep(400000);
}

void runReplicationInteractive(simulationData * simData, simulationState * simState,synSimBuffer * simBuff, synInputBuffer * inputBuff) {
    synShmSimBufferPush(simBuff, simState);
    //} else if (simState->mode == interactive) {
    for (int i = 0; i < simData->height; i++) {
        for (int j = 0; j < simData->width; j++) {
            if (i == simData->centerY && j == simData->centerX) {
                continue;
            }
            coordinates initialCoor = {j, i};
            runTileInteractive(simData, simState, &initialCoor, simBuff, inputBuff);
        }
    }
    usleep(400000);
}