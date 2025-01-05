//
// Created by Vladimir on 2. 1. 2025.
//

#ifndef NAMES_H
#define NAMES_H

typedef struct shared_names {
    char *shm_name_;
    char *mut_pc_;
    char *sem_produce_;
    char *sem_consume_;
} shared_names;

char * add_suffix(const char * name, const char * suffix);
void destroy_names(shared_names * names);
#endif //NAMES_H
