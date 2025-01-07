//
// Created by Vladimir on 5. 1. 2025.
//

#ifndef SIMULATION_H
#define SIMULATION_H

#define MAX_WIDTH 10
#define MAX_HEIGHT 10
#include <stdbool.h>

typedef struct simulationData {
    int width;
    int height;
    int replications;
    int up;     //kumulativne - napr ak vsetky maju rovnaku sancu, tak up = 25, down = 50, left = 75, right = 100
    int down;
    int left;
    int right;
    int maxSteps;
    char filePath[128];

    int centerX;
    int centerY;
}simulationData;

typedef struct simulationState {
    int tile[MAX_WIDTH][MAX_HEIGHT];
    int currentX;
    int currentY;
    bool ended;
}simulationState;

typedef enum simulationMode {
    average,
    probability,
    interactive,
    paused,
    stop
} simulationMode;

void initSimData(simulationData* simData, char * stringData);
void initSimState(simulationState* simState, simulationData* simData);
void destroySimState(simulationState * simState);

#endif //SIMULATION_H
