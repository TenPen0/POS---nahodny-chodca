//
// Created by Vladimir on 2. 1. 2025.
//

#include "synBuffer.h"

#include <stdio.h>
#include <stdlib.h>

void syn_shm_buffer_init(shared_names *names) {
    if (sem_open(names->mut_pc_, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1) == SEM_FAILED) {
        perror("Failed to create mutPC");
        exit(EXIT_FAILURE);
    }

    /*if (sem_open(names->sem_produce_, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, BUFF_SIZE) == SEM_FAILED) {
        perror("Failed to create Produce");
        exit(EXIT_FAILURE);
    }*/

    if (sem_open(names->sem_consume_, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0) == SEM_FAILED) {
        perror("Failed to create Consume");
        exit(EXIT_FAILURE);
    }
}
void syn_shm_buffer_destroy(shared_names *names) {
    if (sem_unlink(names->mut_pc_) ==-1) {
        perror("Failed to unlink mutPC");
        exit(EXIT_FAILURE);
    }
    /*if (sem_unlink(names->sem_produce_) ==-1) {
        perror("Failed to unlink produce");
        exit(EXIT_FAILURE);
    }*/
    if (sem_unlink(names->sem_consume_) ==-1) {
        perror("Failed to unlink consume");
        exit(EXIT_FAILURE);
    }
}
void syn_shm_sim_buffer_open(synSimBuffer *this, shared_names *names) {
    shm_sim_buffer_open(names, &this->buff_, &this->buff_fd_);

    this->mut_pc_ = sem_open(names->mut_pc_, O_RDWR);
    if (this->mut_pc_ == SEM_FAILED) {
        perror("Failed to open <NAME>");
        exit(EXIT_FAILURE);
    }
    this->sem_consume_ = sem_open(names->sem_consume_, O_RDWR);
    if (this->sem_consume_ == SEM_FAILED) {
        perror("Failed to open <NAME>");
        exit(EXIT_FAILURE);
    }
    /*this->sem_produce_ = sem_open(names->sem_produce_, O_RDWR);
    if ( this->sem_produce_ == SEM_FAILED) {
        perror("Failed to open <NAME>");
        exit(EXIT_FAILURE);
    }*/
}
void syn_shm_sim_buffer_close(synSimBuffer *this) {
    shm_sim_buffer_close(this->buff_fd_,this->buff_);

    if (sem_close(this->mut_pc_) ==-1) {
        perror("Failed to close mutPC");
        exit(EXIT_FAILURE);
    }
    if (sem_close(this->sem_consume_) ==-1) {
        perror("Failed to close consume");
        exit(EXIT_FAILURE);
    }
    /*if (sem_close(this->sem_produce_) ==-1) {
        perror("Failed to close produce");
        exit(EXIT_FAILURE);
    }*/
}
void syn_shm_sim_buffer_push(synSimBuffer *this, const simulationState *input) {
    //sem_wait(this->sem_produce_);
    sem_wait(this->mut_pc_);
    if (this->buff_->size >= 1) {       //ak sa v bufferi nachadzala hodnota, prepise sa a postne semafor condume
        simBuffPush(this->buff_, input);
        sem_post(this->mut_pc_);
    } else {
        simBuffPush(this->buff_, input);
        sem_post(this->mut_pc_);
        sem_post(this->sem_consume_);
    }
}
void syn_shm_sim_buffer_pop(synSimBuffer *this, simulationState *output) {
    sem_wait(this->sem_consume_);
    sem_wait(this->mut_pc_);
    simBuffPop(this->buff_, output);
    sem_post(this->mut_pc_);
    //sem_post(this->sem_produce_);
}

void syn_shm_sim_buffer_read(synSimBuffer *this, simulationState *output) {
    sem_wait(this->mut_pc_);
    simBuffRead(this->buff_, output);
    sem_post(this->mut_pc_);
}

void syn_shm_input_buffer_open(synInputBuffer *this, shared_names *names) {
    shm_input_buffer_open(names, &this->buff_, &this->buff_fd_);

    this->mut_pc_ = sem_open(names->mut_pc_, O_RDWR);
    if (this->mut_pc_ == SEM_FAILED) {
        perror("Failed to open <NAME>");
        exit(EXIT_FAILURE);
    }
    this->sem_consume_ = sem_open(names->sem_consume_, O_RDWR);
    if (this->sem_consume_ == SEM_FAILED) {
        perror("Failed to open <NAME>");
        exit(EXIT_FAILURE);
    }
}

void syn_shm_input_buffer_close(synInputBuffer *this) {
    shm_input_buffer_close(this->buff_fd_,this->buff_);

    if (sem_close(this->mut_pc_) ==-1) {
        perror("Failed to close mutPC");
        exit(EXIT_FAILURE);
    }
    if (sem_close(this->sem_consume_) ==-1) {
        perror("Failed to close consume");
        exit(EXIT_FAILURE);
    }
}

void syn_shm_input_buffer_push(synInputBuffer *this, const simulationMode *input) {
    sem_wait(this->mut_pc_);
    if (this->buff_->size >= 1) {       //ak sa v bufferi nachadzala hodnota, prepise sa a postne semafor consume
        inputBuffPush(this->buff_, input);
        sem_post(this->mut_pc_);
    } else {
        inputBuffPush(this->buff_, input);
        sem_post(this->mut_pc_);
        sem_post(this->sem_consume_);
    }
}

void syn_shm_input_buffer_pop(synInputBuffer *this, simulationMode *output) {
    sem_wait(this->sem_consume_);
    sem_wait(this->mut_pc_);
    inputBuffPop(this->buff_, output);
    sem_post(this->mut_pc_);
}

void syn_shm_input_buffer_read(synInputBuffer *this, simulationMode *output) {
    sem_wait(this->mut_pc_);
    inputBuffRead(this->buff_, output);
    sem_post(this->mut_pc_);
}


