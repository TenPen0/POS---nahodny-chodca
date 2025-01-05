//
// Created by Vladimir on 5. 1. 2025.
//

#include "simulation.h"

#include <stdio.h>
#include <stdlib.h>

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
        &simData->filePath);

    //kumulativne
    simData->down = simData->down + simData->up;
    simData->left = simData->left + simData->down;
    simData->right = simData->right - simData->left;

    simData->centerX = simData->width / 2;
    simData->centerY = simData->height / 2;
}


void initSimState(simulationState* simState, simulationData* simData) {
    for (int i = 0; i < simData->width; i++) {
        for (int j = 0; j < simData->height; j++) {
            simState->tile[i][j] = 0;
        }
    }
    simState->currentX = 0;
    simState->currentY = 0;
    simState->ended = false;
}

void destroySimState(simulationState * simState) {
    /*free(simState->tile);
    simState = NULL;*/
}