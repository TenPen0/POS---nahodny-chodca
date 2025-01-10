//
// Created by Vladimir on 4. 1. 2025.
//

#include "server.h"

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "simThread.h"
#include "../shm/names.h"
#include "../shm/synBuffer.h"
#include "simulation.h"
#include "../client/drawThread.h"


bool checkCenter(simulationData * simData, coordinates * currentCoor) {
    if (currentCoor->y == simData->centerY && currentCoor->x == simData->centerX) {
        return true;
    } else {
        return false;
    }
}

void moveUp(coordinates * initialCoor, coordinates * currentCoor, tile (* tiles)[MAX_WIDTH][MAX_HEIGHT]) {
    if (currentCoor->y > 0) {
        currentCoor->y--;
    }
    (*tiles)[initialCoor->x][initialCoor->y].steps++;
}

void moveDown(coordinates * initialCoor, coordinates * currentCoor, tile (* tiles)[MAX_WIDTH][MAX_HEIGHT], simulationData* simData) {
    if (currentCoor->y < simData->height - 1) {
        currentCoor->y++;
    }
    (*tiles)[initialCoor->x][initialCoor->y].steps++;
}

void moveLeft(coordinates * initialCoor, coordinates * currentCoor, tile (* tiles)[MAX_WIDTH][MAX_HEIGHT]) {
    if (currentCoor->x > 0) {
        currentCoor->x--;
    }
    (*tiles)[initialCoor->x][initialCoor->y].steps++;
}

void moveRight(coordinates * initialCoor, coordinates * currentCoor, tile (* tiles)[MAX_WIDTH][MAX_HEIGHT], simulationData* simData) {
    if (currentCoor->x < simData->width - 1) {
        currentCoor->x++;
    }
    (*tiles)[initialCoor->x][initialCoor->y].steps++;
}

void runTileSummary(simulationData * simData, coordinates *initialCoor, tile (* tiles)[MAX_WIDTH][MAX_HEIGHT]) {
    coordinates currentCoor = {initialCoor->x, initialCoor->y};
    for (int i = 0; i < simData->maxSteps; i++) {
        int direction = rand() % 100;
        if (direction < simData->up) {
            moveUp(initialCoor, &currentCoor, tiles);
        } else if (direction < simData->down) {
            moveDown(initialCoor, &currentCoor, tiles, simData);
        } else if (direction < simData->left) {
            moveLeft(initialCoor, &currentCoor, tiles);
        } else if (direction < simData->right) {
            moveRight(initialCoor, &currentCoor, tiles, simData);
        }

        if (checkCenter(simData, &currentCoor)) {
            (*tiles)[initialCoor->x][initialCoor->y].successfull++;
            return;
        }
    }
    //nedosiel do ciela
    (*tiles)[initialCoor->x][initialCoor->y].steps -= simData->maxSteps;
}

void runTileInteractive(simulationData * simData, simulationState * simState, coordinates *initialCoor, synSimBuffer * simBuff, synInputBuffer * inputBuff) {
    simState->currentCoor = *initialCoor;
    for (int i = 0; i < simData->maxSteps; i++) {
        if (syn_shm_input_buffer_is_available(inputBuff)) {
            syn_shm_input_buffer_pop(inputBuff, &simState->mode);
        }
        int direction = rand() % 100;
        if (direction < simData->up) {
            moveUp(initialCoor, &simState->currentCoor, &simState->tiles);
        } else if (direction < simData->down) {
            moveDown(initialCoor, &simState->currentCoor, &simState->tiles, simData);
        } else if (direction < simData->left) {
            moveLeft(initialCoor, &simState->currentCoor, &simState->tiles);
        } else if (direction < simData->right) {
            moveRight(initialCoor, &simState->currentCoor, &simState->tiles, simData);
        }

        if (syn_shm_input_buffer_is_available(inputBuff)) {
            syn_shm_input_buffer_pop(inputBuff, &simState->mode);
        }
        if (simState->mode == interactive) {
            if (checkCenter(simData, &simState->currentCoor)) {
                simState->tiles[initialCoor->x][initialCoor->y].successfull++;
                syn_shm_sim_buffer_push(simBuff, simState);
                return;
            }
            syn_shm_sim_buffer_push(simBuff, simState);
            usleep(400000);
        } else {
            if (checkCenter(simData, &simState->currentCoor)) {
                simState->tiles[initialCoor->x][initialCoor->y].successfull++;
                return;
            }
        }
    }
    //nedosiel do ciela
    simState->tiles[initialCoor->x][initialCoor->y].steps -= simData->maxSteps;
}

void runReplicationSummary(simulationData * simData, simulationState * simState, synSimBuffer * simBuff, synInputBuffer * inputBuff) {
    //simState->replication++;
    //syn_shm_input_buffer_read(inputBuff, &simState->mode);
    /*if (syn_shm_input_buffer_is_available(inputBuff)) {
        syn_shm_input_buffer_pop(inputBuff, &simState->mode);
    }*/
    //if (simState->mode == average || simState->mode == probability) {
        int threads = (simData->width / 5) + 1;
        int widthPerThread = simData->width / threads;
        pthread_t id[threads];
        simThreadData sData[threads];
        for (int i = 0; i < threads; i++) {
            int startColumn = widthPerThread * i;
            int endColumn = widthPerThread * (i + 1) - 1;
            if (i == (threads - 1)) {
                endColumn = simData->width;
            }
            simTheadDataInit(&sData[i],startColumn, endColumn, simState->tiles, simData);
            pthread_create(&id[i], NULL, simThread, &sData[i]);
        }
        for (int i = 0; i < threads; i++) {
            pthread_join(id[i], NULL);
        }
    syn_shm_sim_buffer_push(simBuff, simState);
    usleep(400000);
        /*for (int y = 0; y < simData->height; y++) {
            for (int x = 0; x < simData->width; x++) {
                if (y == simData->centerY && x == simData->centerX) {
                    continue;
                }
                coordinates initialCoor = {x,y};
                runTile(simData, &initialCoor, &simState->tiles);
            }
        }*/
        /*for (int i = 0; i < threads; i++) {
            pthread_join(id[i], NULL);
        }
        syn_shm_sim_buffer_push(simBuff, simState);
        usleep(400000);
    //} else if (simState->mode == interactive) {
        for (int i = 0; i < simData->height; i++) {
            for (int j = 0; j < simData->width; j++) {
                if (i == simData->centerY && j == simData->centerX) {
                    continue;
                }
                coordinates initialCoor = {j, i};
                runTileInteractive(simData, simState, &initialCoor, simBuff, inputBuff);
            }
        }*/
    /*} else if (simState->mode == stop) {
        simState->ended = true;
    }*/
}

void runReplicationInteractive(simulationData * simData, simulationState * simState,synSimBuffer * simBuff, synInputBuffer * inputBuff) {
    syn_shm_sim_buffer_push(simBuff, simState);
    //} else if (simState->mode == interactive) {
    for (int i = 0; i < simData->height; i++) {
        for (int j = 0; j < simData->width; j++) {
            if (i == simData->centerY && j == simData->centerX) {
                continue;
            }
            coordinates initialCoor = {j, i};
            runTileInteractive(simData, simState, &initialCoor, simBuff, inputBuff);
        }
    }

    usleep(400000);
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
        simState.replication++;

        if (syn_shm_input_buffer_is_available(&inputBuff)) {
            syn_shm_input_buffer_pop(&inputBuff, &simState.mode);
        }
        if (simState.mode == average || simState.mode == probability) {
            runReplicationSummary(&simData, &simState, &buff, &inputBuff);
        } else if (simState.mode == interactive) {
            runReplicationInteractive(&simData, &simState, &buff, &inputBuff);
        } else if (simState.mode == stop) {
            simState.ended = true;
        }

        if (simState.ended == true) {
            break;
        }
    }
    simState.ended = true;
    syn_shm_sim_buffer_push(&buff, &simState);

    FILE *file = fopen(simData.filePath, "w");
    fprintf(file, "Ulozena simulacia\n");
    fprintf(file, "%d %d %d %d\n%d %d %d %d\n%d\n",
        simData.width, simData.height, simData.replications, simState.replication,
        simData.up, simData.down, simData.left, simData.right,
        simData.maxSteps);
    drawBoard(&simData, &simState, &drawAverageTile, file);
    drawBoard(&simData, &simState, &drawProbabilityTile, file);
    fclose(file);

    syn_shm_sim_buffer_close(&buff);
    syn_shm_input_buffer_close(&inputBuff);
    destroySimState(&simState);
    destroy_names(&names);
    destroy_names(&inputNames);
}
