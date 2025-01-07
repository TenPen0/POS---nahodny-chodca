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
        simState->currentX++;
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

void runTileInteractive(simulationData * simData, simulationState * simState, int initialX, int initialY, synSimBuffer * simBuff) {
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
        syn_shm_sim_buffer_push(simBuff, simState);
        if (checkCenter(simData, simState)) {
            return;
        }
        usleep(100000);
    }
}

void runReplication(simulationData * simData, simulationState * simState, synSimBuffer * buff, synInputBuffer * inputBuff) {
    simulationMode simMode;
    syn_shm_input_buffer_read(inputBuff, &simMode);
    if (simMode == average || simMode == probability) {
        for (int i = 0; i < simData->height; i++) {
            for (int j = 0; j < simData->width; j++) {
                if (i == simData->centerY && j == simData->centerX) {
                    continue;
                }
                runTile(simData, simState, j, i);
            }
        }
        syn_shm_sim_buffer_push(buff, simState);
        usleep(200000);
    } else if (simMode == interactive) {
        for (int i = 0; i < simData->height; i++) {
            for (int j = 0; j < simData->width; j++) {
                if (i == simData->centerY && j == simData->centerX) {
                    continue;
                }
                runTileInteractive(simData, simState, j, i, buff);
            }
        }
    }
}

int main(int argc, char * argv[]) {
    srand(time(NULL));
    shared_names names;
    names.shm_name_ = add_suffix("S-SHM", argv[1]);
    names.mut_pc_ = add_suffix("S-MUT-PC", argv[1]);
    names.sem_produce_ = add_suffix("S-SEM-P", argv[1]);
    names.sem_consume_ = add_suffix("S-SEM-C", argv[1]);

    shared_names inputNames;
    inputNames.shm_name_ = add_suffix("I-SHM", argv[1]);
    inputNames.mut_pc_ = add_suffix("I-MUT-PC", argv[1]);
    inputNames.sem_produce_ = add_suffix("I-SEM-P", argv[1]);
    inputNames.sem_consume_ = add_suffix("I-SEM-C", argv[1]);

    simulationData simData;
    initSimData(&simData, argv[2]);
    simulationState simState;
    initSimState(&simState, &simData);

    synSimBuffer buff;
    syn_shm_sim_buffer_open(&buff, &names);

    synInputBuffer inputBuff;
    syn_shm_input_buffer_open(&inputBuff, &inputNames);


    for (int i = 0; i < simData.replications; i++) {
        runReplication(&simData, &simState, &buff, &inputBuff);
    }
    simState.ended = true;
    syn_shm_sim_buffer_push(&buff, &simState);

    syn_shm_sim_buffer_close(&buff);
    destroySimState(&simState);
    destroy_names(&names);
}
