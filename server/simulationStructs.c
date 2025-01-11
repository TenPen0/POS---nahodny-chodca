//
// Created by Vladimir on 5. 1. 2025.
//

#include "simulationStructs.h"

#include <stdio.h>

void initSimData(simulationData* simData, char * stringData) {
    sscanf(stringData, "%d %d %d %d %d %d %d %d %s",
        &simData->width,
        &simData->height,
        &simData->replications,
        &simData->up,
        &simData->down,
        &simData->left,
        &simData->right,
        &simData->maxSteps,
        simData->filePath);


    simData->centerX = simData->width / 2;
    simData->centerY = simData->height / 2;
}


void initSimState(simulationState* simState, simulationData* simData) {
    for (int i = 0; i < simData->width; i++) {
        for (int j = 0; j < simData->height; j++) {
            simState->tiles[i][j].steps = 0;
            simState->tiles[i][j].successfulls = 0;
        }
    }
    simState->replication = 0;
    simState->currentCoor.x = 0;
    simState->currentCoor.y = 0;
    simState->mode = average;
    simState->ended = false;
}
