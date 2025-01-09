//
// Created by Vladimir on 5. 1. 2025.
//

#ifndef SIMULATION_H
#define SIMULATION_H

#define MAX_WIDTH 23
#define MAX_HEIGHT 17
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

typedef enum simulationMode {
    average,
    probability,
    interactive,
    paused,
    stop
} simulationMode;

typedef struct tile {
    int steps;
    int successfull;
}tile;

typedef struct coordinations{
    int x;
    int y;
} coordinates;

typedef struct simulationState {
    tile tiles[MAX_WIDTH][MAX_HEIGHT];
    int replication;
    coordinates currentCoor;
    simulationMode mode;
    bool ended;
}simulationState;


void initSimData(simulationData* simData, char * stringData);
void initSimState(simulationState* simState, simulationData* simData);
void destroySimState(simulationState * simState);

#endif //SIMULATION_H
