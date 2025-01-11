//
// Created by Vladimir on 2. 1. 2025.
//

#ifndef SHM_H
#define SHM_H

#include "names.h"
#include "buffer.h"


void shmSimInit(sharedNames *names);
void shmInputInit(sharedNames *names);
void shmDestroy(sharedNames *names);

void shmSimBufferOpen(sharedNames *names, simBuffer **out_buff, int *out_fd_shm);
void shmSimBufferClose(int fd_shm, simBuffer *buff);

void shmInputBufferOpen(sharedNames *names, inputBuffer **out_buff, int *out_fd_shm);
void shmInputBufferClose(int fd_shm, inputBuffer *buff);

#endif //SHM_H
