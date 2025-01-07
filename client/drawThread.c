//
// Created by Vladimir on 6. 1. 2025.
//

#include "drawThread.h"

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "../shm/synBuffer.h"

void drawBoard(int height, int width, simulationState * simState) {
    for (int x = 0; x < (width*4)+1; x++) {
        printf("-");
    }
    printf("\n");
    for (int y = 0; y < height; y++) {
        printf("|");
        for (int x = 0; x < width; x++) {
            printf("%3d|",simState->tile[x][y]);
        }
        printf("\n");
        for (int x = 0; x < (width*4)+1; x++) {
            printf("-");
        }
        printf("\n");
    }

    printf("\n\n");
}

void drawThreadDataInit(drawThreadData *this, shared_names *simNames) {
    this->simNames = simNames;
}


void * drawThread(void * args) {
    drawThreadData * data = args;
    synSimBuffer buffer;
    syn_shm_sim_buffer_open(&buffer, data->simNames);

    simulationState simState;

    while (true) {
        syn_shm_sim_buffer_pop(&buffer, &simState);
        if (simState.ended) {
            break;
        }
        drawBoard(5,7, &simState);
        usleep(500000);
    }

    syn_shm_sim_buffer_close(&buffer);
    return NULL;
}
