//
// Created by Vladimir on 8. 1. 2025.
//

#include "simThread.h"

#include <stddef.h>

#include "server.h"

void simTheadDataInit(simThreadData *data, int startWidth, int endWidth, tile (* tiles)[MAX_WIDTH][MAX_HEIGHT], simulationData *simData) {
    data->startWidth = startWidth;
    data->endWidth = endWidth;
    data->tiles = tiles;
    data->simData = simData;

}

void * simThread(void *args) {
    simThreadData *data = args;
    for (int x = data->startWidth; x <= data->endWidth; x++) {
        for (int y = 0; y <= data->simData->height; y++) {
            //runTile(data->simData, );
        }
    }
    return NULL;
}
