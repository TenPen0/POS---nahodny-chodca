//
// Created by Vladimir on 10. 1. 2025.
//

#ifndef SIMULATIONSTRUCTS_H
#define SIMULATIONSTRUCTS_H

#include "simulationStructs.h"

#include "../shm/synBuffer.h"

void moveUp(coordinates * initialCoor, coordinates * currentCoor, tile (* tiles)[MAX_WIDTH][MAX_HEIGHT]);
void moveDown(coordinates * initialCoor, coordinates * currentCoor, tile (* tiles)[MAX_WIDTH][MAX_HEIGHT], simulationData* simData);
void moveLeft(coordinates * initialCoor, coordinates * currentCoor, tile (* tiles)[MAX_WIDTH][MAX_HEIGHT]);
void moveRight(coordinates * initialCoor, coordinates * currentCoor, tile (* tiles)[MAX_WIDTH][MAX_HEIGHT], simulationData* simData);
bool checkCenter(simulationData * simData, coordinates * currentCoor);

void runTileSummary(simulationData * simData, coordinates *initialCoor, tile (* tiles)[MAX_WIDTH][MAX_HEIGHT]);
void runTileInteractive(simulationData * simData, simulationState * simState, coordinates *initialCoor, synSimBuffer * simBuff, synInputBuffer * inputBuff);
void runReplicationSummary(simulationData * simData, simulationState * simState, synSimBuffer * simBuff, synInputBuffer * inputBuff);
void runReplicationInteractive(simulationData * simData, simulationState * simState,synSimBuffer * simBuff, synInputBuffer * inputBuff);

#endif //SIMULATIONSTRUCTS_H
