//
// Created by Vladimir on 4. 1. 2025.
//

#include "server.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../shm/names.h"
#include "../shm/synBuffer.h"
#include "simulation.h"


bool checkCenter(simulationData * simData, simulationState * simState) {
    if (simState->currentY == simData->centerY && simState->currentX == simData->centerX) {
        return true;
    } else {
        return false;
    }
}

void moveUp(simulationData* simData, simulationState * simState, int initialX, int initialY) {
    if (simState->currentY > 0) {
        simState->currentY--;
    }
    simState->tile[initialX][initialY]++;
}

void moveDown(simulationData* simData, simulationState * simState, int initialX, int initialY) {
    if (simState->currentY < simData->height - 1) {
        simState->currentY++;
    }
    simState->tile[initialX][initialY]++;
}

void moveLeft(simulationData* simData, simulationState * simState, int initialX, int initialY) {
    if (simState->currentX > 0) {
        simState->currentX--;
    }
    simState->tile[initialX][initialY]++;
}

void moveRight(simulationData* simData, simulationState * simState, int initialX, int initialY) {
    if (simState->currentX < simData->width - 1) {
        simState->currentY++;
    }
    simState->tile[initialX][initialY]++;
}

void runTile(simulationData * simData, simulationState * simState, int initialX, int initialY) {
    simState->currentX = initialX;
    simState->currentY = initialY;
    for (int i = 0; i < simData->maxSteps; i++) {
        int direction = rand() % 100;
        if (direction < simData->up) {
            moveUp(simData, simState, initialX, initialY);
        } else if (direction < simData->down) {
            moveDown(simData, simState, initialX, initialY);
        } else if (direction < simData->left) {
            moveLeft(simData, simState, initialX, initialY);
        } else if (direction < simData->right) {
            moveRight(simData, simState, initialX, initialY);
        }

        if (checkCenter(simData, simState)) {
            return;
        }
    }
}

void runReplication(simulationData * simData, simulationState * simState, synBuffer * buff) {
    for (int i = 0; i < simData->height; i++) {
        for (int j = 0; j < simData->width; j++) {
            if (i == simData->centerY && j == simData->centerX) {
                continue;
            }
            runTile(simData, simState, j, i);
            syn_shm_buffer_push(buff, simState);
            usleep(20000);
        }
    }
}

int main(int argc, char * argv[]) {
    srand(time(NULL));
    shared_names names;
    names.shm_name_ = add_suffix("SHM", argv[1]);
    names.mut_pc_ = add_suffix("MUT-PC", argv[1]);
    names.sem_produce_ = add_suffix("SEM-P", argv[1]);
    names.sem_consume_ = add_suffix("SEM-C", argv[1]);

    simulationData simData;
    initSimData(&simData, argv[2]);
    simulationState simState;
    initSimState(&simState, &simData);

    synBuffer buff;
    syn_shm_buffer_open(&buff, &names);

    for (int i = 0; i < simData.replications; i++) {
        runReplication(&simData, &simState, &buff);
    }
    simState.ended = true;
    syn_shm_buffer_push(&buff, &simState);

    syn_shm_buffer_close(&buff);
    destroySimState(&simState);
    destroy_names(&names);
}
