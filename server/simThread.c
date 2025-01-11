//
// Created by Vladimir on 8. 1. 2025.
//

#include "simThread.h"

#include "simulation.h"
#include <stdlib.h>

void simTheadDataInit(simThreadData *data, int startWidth, int endWidth, tile (* tiles)[MAX_WIDTH][MAX_HEIGHT], simulationData *simData) {
    data->startColumn = startWidth;
    data->endColumn = endWidth;
    data->tiles = tiles;
    data->simData = simData;

}

void * simThread(void *args) {
    simThreadData *data = args;
    for (int x = data->startColumn; x <= data->endColumn; x++) {
        for (int y = 0; y < data->simData->height; y++) {
            coordinates initialCoor = {x, y};
            runTileSummary(data->simData, &initialCoor, data->tiles);
        }
    }
    return NULL;
}
