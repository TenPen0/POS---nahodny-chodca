//
// Created by Vladimir on 4. 1. 2025.
//

#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#include "simulation.h"
#include "../shm/names.h"
#include "../shm/synBuffer.h"
#include "simulationStructs.h"
#include "../client/drawThread.h"



int main(int argc, char * argv[]) {
    srand(time(NULL));
    sharedNames simNames;
    simNames.shmName = addSuffix("S-SHM", argv[1]);
    simNames.mut = addSuffix("S-MUT-PC", argv[1]);
    simNames.semProduce = addSuffix("S-SEM-P", argv[1]);
    simNames.semConsume = addSuffix("S-SEM-C", argv[1]);

    sharedNames inputNames;
    inputNames.shmName = addSuffix("I-SHM", argv[1]);
    inputNames.mut = addSuffix("I-MUT-PC", argv[1]);
    inputNames.semProduce = addSuffix("I-SEM-P", argv[1]);
    inputNames.semConsume = addSuffix("I-SEM-C", argv[1]);

    simulationData simData;
    initSimData(&simData, argv[2]);
    simulationState simState;
    initSimState(&simState, &simData);

    synSimBuffer simBuff;
    synShmSimBufferOpen(&simBuff, &simNames);
    synInputBuffer inputBuff;
    synShmInputBufferOpen(&inputBuff, &inputNames);


    for (int i = 0; i < simData.replications; i++) {
        simState.replication++;

        if (synShmInputBufferIsAvailable(&inputBuff)) {
            synShmInputBufferPop(&inputBuff, &simState.mode);
        }
        if (simState.mode == average || simState.mode == probability) {
            runReplicationSummary(&simData, &simState, &simBuff, &inputBuff);
        } else if (simState.mode == interactive) {
            runReplicationInteractive(&simData, &simState, &simBuff, &inputBuff);
        } else if (simState.mode == stop) {
            simState.ended = true;
        }

        if (simState.ended == true) {
            break;
        }
    }

    simState.ended = true;
    synShmSimBufferPush(&simBuff, &simState);

    FILE *file = fopen(simData.filePath, "w");
    fprintf(file, "Ulozena simulacia\n");
    fprintf(file, "%d %d %d %d\n%d %d %d %d\n%d\n",
        simData.width, simData.height, simData.replications, simState.replication,
        simData.up, simData.down, simData.left, simData.right,
        simData.maxSteps);
    drawBoard(&simData, &simState, &drawAverageTile, file);
    drawBoard(&simData, &simState, &drawProbabilityTile, file);
    fclose(file);

    synShmSimBufferClose(&simBuff);
    synShmInputBufferClose(&inputBuff);
    destroyNames(&simNames);
    destroyNames(&inputNames);
}
