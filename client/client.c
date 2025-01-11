//
// Created by Vladimir on 3. 1. 2025.
//

#include <sys/wait.h>

#include "menu.h"
#include "../shm/synBuffer.h"

int main(int argc, const char * argv[]) {
    const char * suffix = "nahodnachodza";

    sharedNames simNames;
    simNames.shmName = addSuffix("S-SHM", suffix);
    simNames.mut = addSuffix("S-MUT-PC", suffix);
    simNames.semProduce = addSuffix("S-SEM-P", suffix);
    simNames.semConsume = addSuffix("S-SEM-C", suffix);

    sem_t *mutS, *semProduceS, *semConsumeS;
    sem_t *mutI, *semProduceI, *semConsumeI;

    shmSimInit(&simNames);
    synShmBufferInit(&simNames, &mutS, &semProduceS, &semConsumeS);

    sharedNames inputNames;
    inputNames.shmName = addSuffix("I-SHM", suffix);
    inputNames.mut = addSuffix("I-MUT-PC", suffix);
    inputNames.semProduce = addSuffix("I-SEM-P", suffix);
    inputNames.semConsume = addSuffix("I-SEM-C", suffix);
    shmInputInit(&inputNames);
    synShmBufferInit(&inputNames, &mutI, &semProduceI, &semConsumeI);

    bool end = false;
    do {
        drawMenu();
        int choice = readInt(1,5);
        switch (choice) {
            case 1:
                newSimulation(suffix,&inputNames,&simNames);
                break;
            case 2:
                loadSimulation(suffix,&inputNames,&simNames);
                break;
            case 3:
                showResult();
                break;
            case 4:
                controls();
                break;
            case 5:
                end = true;
                break;
            default:
                break;
        }
    } while (!end);

    int status;
    wait(&status);


    synShmBufferDestroy(&simNames, mutS, semProduceS, semConsumeS);
    shmDestroy(&simNames);

    synShmBufferDestroy(&inputNames, mutI, semProduceI, semConsumeI);
    shmDestroy(&inputNames);

    destroyNames(&inputNames);
    destroyNames(&simNames);
}
