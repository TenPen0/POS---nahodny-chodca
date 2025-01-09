//
// Created by Vladimir on 6. 1. 2025.
//

#include "drawThread.h"

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "../shm/synBuffer.h"

void drawAverageTile(simulationState * simState, int x, int y, FILE * file) {
    double avg = 0;
    if (simState->tiles[x][y].successfull != 0) {
        avg = simState->tiles[x][y].steps / (double) simState->tiles[x][y].successfull;
    }
    if (avg < 100 )
        fprintf(file,"%4.1f|", avg);
    else
        fprintf(file, "%4.0f|", avg);
    ;
}

void drawProbabilityTile(simulationState * simState, int x, int y, FILE * file) {
    int probability = simState->tiles[x][y].successfull * 100 / simState->replication;
    fprintf(file, "%3d%%|", probability);
}

void drawInteractiveTile(simulationState * simState, int x, int y, FILE * file) {
    if (x == simState->currentCoor.x && y == simState->currentCoor.y) {
        fprintf(file, " xx |");
    } else {
        fprintf(file, "    |");
    }
}

void drawBoard(int width, int height, simulationState * simState, void(*drawTile)(simulationState*, int, int, FILE*), FILE * file) {
    for (int x = 0; x < (width*5)+1; x++) {
        fprintf(file, "-");    //horne ohranicenie
    }
    fprintf(file, "\n");
    for (int y = 0; y < height; y++) {
        fprintf(file, "|");    //zaciatok riadka
        for (int x = 0; x < width; x++) {
            if (x == (width / 2) && y == (height / 2)) {
                fprintf(file, "////|");     //stred
            } else {
                drawTile(simState, x, y, file);
            }
        }
        fprintf(file, "\n");
        for (int x = 0; x < (width*5)+1; x++) {
            fprintf(file, "-");    //dolne ohranicenie
        }
        fprintf(file, "\n");
    }


    fprintf(file, "\n\n");
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
            printf("Simulacia skoncila. Stlac Enter pre pokracovanie.\n");
            break;
        }
        if (simState.mode == average) {
            drawBoard(5,5, &simState, &drawAverageTile, stdout);
        } else if (simState.mode == probability) {
            drawBoard(5,5, &simState, &drawProbabilityTile, stdout);
        } else if (simState.mode == interactive) {
            drawBoard(5,5, &simState, &drawInteractiveTile, stdout);
        }
    }

    syn_shm_sim_buffer_close(&buffer);
    return NULL;
}
