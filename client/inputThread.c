//
// Created by Vladimir on 6. 1. 2025.
//

#include "inputThread.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readInt(int min, int max) {
    while (1) {
        char inputBuff[32];
        scanf("%s",&inputBuff);
        if (strlen(inputBuff) == 1) {
            if (isdigit(inputBuff[0])) {
                int choice = atoi(inputBuff);
                if (choice >= min && choice <= max) {
                    return choice;
                }
            }
        }
        printf("Chybna volba, zadaj znova\n");
    }
}
void * inputThread(void * args) {
    inputThreadData * data = args;
    synInputBuffer inputBuff;
    syn_shm_input_buffer_open(&inputBuff, data->inputNames);

    simulationMode simMode;
    while (1) {
        int input = readInt(1, 4);
        switch (input) {
            case 1:
                simMode = average;
            syn_shm_input_buffer_push(&inputBuff, &simMode);
                break;
            case 2:
                simMode = probability;
                syn_shm_input_buffer_push(&inputBuff, &simMode);
                break;
            case 3:
                simMode = interactive;
                syn_shm_input_buffer_push(&inputBuff, &simMode);
                break;
            case 4:
                simMode = paused;
                syn_shm_input_buffer_push(&inputBuff, &simMode);
                syn_shm_input_buffer_close(&inputBuff);
                return NULL;
            case 5:
                simMode = stop;
                syn_shm_input_buffer_push(&inputBuff, &simMode);
                syn_shm_input_buffer_close(&inputBuff);
                return NULL;
            default:
                printf("Chyba pri citani vstupu v readInt().\n");
            break;
        }
    }
}

void inputThreadInit(inputThreadData * this, shared_names * inputNames, shared_names * simNames) {
    this->inputNames = inputNames;
    //this->simNames = simNames;
}


