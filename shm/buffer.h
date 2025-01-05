//
// Created by Vladimir on 2. 1. 2025.
//

#ifndef BUFFER_H
#define BUFFER_H

#define BUFF_SIZE 1
#include "../server/simulation.h"

typedef struct buffer{
    simulationState simState;
    int capacity;
    int size;
    int in;
    int out;
} buffer;

void buffInit(buffer * this);
void buffPush(buffer * this, const simulationState * in);
void buffPop(buffer * this, simulationState * out);
void destroyBuff(buffer * this);

#endif //BUFFER_H
