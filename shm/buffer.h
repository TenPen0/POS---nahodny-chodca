//
// Created by Vladimir on 2. 1. 2025.
//

#ifndef BUFFER_H
#define BUFFER_H

#define BUFF_SIZE 4
#include "../server/simulationStructs.h"

typedef struct simBuffer{
    simulationState simState[BUFF_SIZE];
    int capacity;
    int size;
    int in;
    int out;
} simBuffer;

void simBuffInit(simBuffer * this);
void simBuffPush(simBuffer * this, const simulationState * in);
void simBuffPop(simBuffer * this, simulationState * out);
bool simBuffReadEnded(simBuffer * this);

typedef struct inputBuffer{
    simulationMode simMode[BUFF_SIZE];
    int capacity;
    int size;
    int in;
    int out;
} inputBuffer;

void inputBuffInit(inputBuffer * this);
void inputBuffPush(inputBuffer * this, const simulationMode * in);
void inputBuffPop(inputBuffer * this, simulationMode * out);
bool inputBufferIsAvailable(inputBuffer * this);

#endif //BUFFER_H
