//
// Created by Vladimir on 6. 1. 2025.
//

#include "inputThread.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../shm/synBuffer.h"

int readIntInputThread() {
    while (1) {
        char inputBuff[32];
        fgets(inputBuff,sizeof(inputBuff), stdin);
        if (strlen(inputBuff) == 1) {
            return -1;
        }
        inputBuff[strlen(inputBuff)-1] = 0;
        for (int i = 0; i < strlen(inputBuff); i++) {
            if (isdigit(inputBuff[i]) == false) {
                return -1;
            }
        }
        int choice = atoi(inputBuff);
        return choice;
    }
}
void * inputThread(void * args) {
    inputThreadData * data = args;
    synInputBuffer inputBuff;
    synShmInputBufferOpen(&inputBuff, data->inputNames);
    synSimBuffer simBuff;
    synShmSimBufferOpen(&simBuff, data->simNames);

    simulationMode simMode;
    while (!synShmSimBufferReadEnded(&simBuff)) {
        int input = readIntInputThread(1, 4);
        switch (input) {
            case 1:
                simMode = average;
                synShmInputBufferPush(&inputBuff, &simMode);
                break;
            case 2:
                simMode = probability;
                synShmInputBufferPush(&inputBuff, &simMode);
                break;
            case 3:
                simMode = interactive;
                synShmInputBufferPush(&inputBuff, &simMode);
                break;
            case 4:
                simMode = stop;
                synShmInputBufferPush(&inputBuff, &simMode);
                break;
            default:
                break;
        }
    }

    synShmInputBufferClose(&inputBuff);
    synShmSimBufferClose(&simBuff);
    return NULL;
}

void inputThreadInit(inputThreadData * this, sharedNames * inputNames, sharedNames * simNames) {
    this->inputNames = inputNames;
    this->simNames = simNames;
}


