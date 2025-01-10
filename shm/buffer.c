//
// Created by Vladimir on 2. 1. 2025.
//

#include "buffer.h"

#include <stdlib.h>

void simBuffInit(simBuffer * this) {
    this->capacity = BUFF_SIZE;
    this->size = 0;
    this->in = 0;
    this->out = 0;
    //this->simState[0].mode = average;

    this->simState[BUFF_SIZE - 1].ended = false; //
}

void simBuffPush(simBuffer * this, const simulationState * in) {
    this->simState[this->in++] = *in;
    this->size++;
    this->in %= this->capacity;
}

void simBuffPop(simBuffer * this, simulationState * out) {
    *out = this->simState[this->out++];
    this->size--;
    this->out %= this->capacity;
}

void destroySimBuff(simBuffer * this){
    //free(this->cislo);
    //this->cislo = NULL;
}

bool simBuffReadEnded(simBuffer *this) {
    if (this->out == 0)
        return this->simState[this->capacity - 1].ended;
    else {
        return this->simState[this->out - 1].ended;
    }
}

/*void simBuffRead(simBuffer *this, simulationState *out) {
    *out = this->simState;
}
*/
void inputBuffInit(inputBuffer *this) {
    this->simMode[0] = average;
    this->size = 0;
    this->out = 0;
    this->capacity = BUFF_SIZE;
    this->size = 0;
}

void inputBuffPush(inputBuffer *this, const simulationMode *in) {
    this->simMode[this->in++] = *in;
    this->size++;
    this->in %= this->capacity;
}

void inputBuffPop(inputBuffer *this, simulationMode *out) {
    *out = this->simMode[this->out++];
    this->size--;
    this->out %= this->capacity;
}

bool inputBufferIsAvailable(inputBuffer *this) {
    return this->size;
}

/*void inputBuffRead(inputBuffer * this, simulationMode *out) {
    *out = this->simMode;
}*/
