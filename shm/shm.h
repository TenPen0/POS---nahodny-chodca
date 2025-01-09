//
// Created by Vladimir on 2. 1. 2025.
//

#ifndef SHM_H
#define SHM_H

#include "names.h"
#include "buffer.h"


void shm_sim_init(shared_names *names);
void shm_input_init(shared_names *names);
void shm_destroy(shared_names *names);

void shm_sim_buffer_open(shared_names *names, simBuffer **out_buff, int *out_fd_shm);
void shm_sim_buffer_close(int fd_shm, simBuffer *buff);

void shm_input_buffer_open(shared_names *names, inputBuffer **out_buff, int *out_fd_shm);
void shm_input_buffer_close(int fd_shm, inputBuffer *buff);

#endif //SHM_H
