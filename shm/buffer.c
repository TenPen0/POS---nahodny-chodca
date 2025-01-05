//
// Created by Vladimir on 2. 1. 2025.
//

#include "buffer.h"

#include <stdlib.h>

void buffInit(buffer * this) {
    //this->cislo = calloc(BUFF_SIZE, sizeof(int));
    this->capacity = BUFF_SIZE;
    this->size = 0;
    this->in = 0;
    this->out = 0;
}

void buffPush(buffer * this, const simulationState * in) {
    this->simState = *in;
    this->size=1;
    /*this->size++;
    this->in %= this->capacity;*/
}

void buffPop(buffer * this, simulationState * out) {
    *out = this->simState;
    this->size=0;
    /**out = this->cislo[this->out++];
    this->size--;
    this->out %= this->capacity;*/
}

void destroyBuff(buffer * this){
    //free(this->cislo);
    //this->cislo = NULL;
}
