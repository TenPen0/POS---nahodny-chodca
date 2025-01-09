//
// Created by Vladimir on 2. 1. 2025.
//

#include "shm.h"
#include <stdio.h>
#include <stdlib.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>


void shm_sim_init(shared_names *names) {
    const int fd_shm = shm_open(names->shm_name_, O_RDWR | O_CREAT | O_EXCL,S_IRUSR | S_IWUSR);
    if (fd_shm ==-1) {
        perror("Failed to create shared memory");
        exit(EXIT_FAILURE);
    }
    if (ftruncate(fd_shm, sizeof(simBuffer)) ==-1) {
        perror("Failed to truncate shared memory");
        exit(EXIT_FAILURE);
    }
    simBuffer *buff = mmap(NULL, sizeof(simBuffer), PROT_READ | PROT_WRITE,
    MAP_SHARED, fd_shm, 0);
    simBuffInit(buff);
    shm_sim_buffer_close(fd_shm, buff);
}

void shm_input_init(shared_names *names) {
    const int fd_shm = shm_open(names->shm_name_, O_RDWR | O_CREAT | O_EXCL,S_IRUSR | S_IWUSR);
    if (fd_shm ==-1) {
        perror("Failed to create shared memory");
        exit(EXIT_FAILURE);
    }
    if (ftruncate(fd_shm, sizeof(simBuffer)) ==-1) {
        perror("Failed to truncate shared memory");
        exit(EXIT_FAILURE);
    }
    inputBuffer *buff = mmap(NULL,sizeof(inputBuffer), PROT_READ | PROT_WRITE,
    MAP_SHARED, fd_shm, 0);
    inputBuffInit(buff);
    shm_input_buffer_close(fd_shm, buff);
}

void shm_destroy(shared_names *names) {
    if (shm_unlink(names->shm_name_) ==-1) {
        perror("Failed to unlink shared memory");
        exit(EXIT_FAILURE);
    }

}
void shm_sim_buffer_open(shared_names *names, simBuffer **out_buff, int *out_fd_shm) {
    const int fd_shm = shm_open(names->shm_name_, O_RDWR, 0);
    if (fd_shm ==-1) {
        perror("Failed to open shared memory");
        exit(EXIT_FAILURE);
    }
    simBuffer *buff = mmap(NULL, sizeof(simBuffer), PROT_READ | PROT_WRITE,
    MAP_SHARED, fd_shm, 0);
    if (buff == MAP_FAILED) {
        perror("Failed to map shared memory");
        exit(EXIT_FAILURE);
    }
    *out_fd_shm = fd_shm;
    *out_buff = buff;
}
void shm_sim_buffer_close(int fd_shm, simBuffer *buff) {
    if (munmap(buff, sizeof(simBuffer)) ==-1) {
        perror("Failed to unmap shared memory");
        exit(EXIT_FAILURE);
    }
    if (close(fd_shm) ==-1) {
        perror("Failed to close shared memory");
        exit(EXIT_FAILURE);
    }

}

void shm_input_buffer_open(shared_names *names, inputBuffer **out_buff, int *out_fd_shm) {
    const int fd_shm = shm_open(names->shm_name_, O_RDWR, 0);
    if (fd_shm ==-1) {
        perror("Failed to open shared memory");
        exit(EXIT_FAILURE);
    }
    inputBuffer *buff = mmap(NULL, sizeof(inputBuffer), PROT_READ | PROT_WRITE,
    MAP_SHARED, fd_shm, 0);
    if (buff == MAP_FAILED) {
        perror("Failed to map shared memory");
        exit(EXIT_FAILURE);
    }
    *out_fd_shm = fd_shm;
    *out_buff = buff;
}

void shm_input_buffer_close(int fd_shm, inputBuffer *buff) {
    if (munmap(buff, sizeof(inputBuffer)) ==-1) {
        perror("Failed to unmap shared memory");
        exit(EXIT_FAILURE);
    }
    if (close(fd_shm) ==-1) {
        perror("Failed to close shared memory");
        exit(EXIT_FAILURE);
    }
}
