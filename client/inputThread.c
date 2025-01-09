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
        fgets(inputBuff,sizeof(inputBuff), stdin);
        if (strlen(inputBuff) == 2) {
            if (isdigit(inputBuff[0])) {
                int choice = atoi(inputBuff);
                if (choice >= min && choice <= max) {
                    return choice;
                }
            }
        }
        else {
            return 0;
        }
        //printf("Chybna volba, zadaj znova\n");
    }
}
void * inputThread(void * args) {
    inputThreadData * data = args;
    synInputBuffer inputBuff;
    syn_shm_input_buffer_open(&inputBuff, data->inputNames);
    synSimBuffer simBuff;
    syn_shm_sim_buffer_open(&simBuff, data->simNames);

    simulationMode simMode;
    while (!syn_shm_sim_buffer_read_ended(&simBuff)) {
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
                simMode = stop;
                syn_shm_input_buffer_push(&inputBuff, &simMode);
                break;
            default:
                break;
        }
    }

    syn_shm_input_buffer_close(&inputBuff);
    syn_shm_sim_buffer_close(&simBuff);
}

void inputThreadInit(inputThreadData * this, shared_names * inputNames, shared_names * simNames) {
    this->inputNames = inputNames;
    this->simNames = simNames;
}


