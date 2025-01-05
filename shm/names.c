//
// Created by Vladimir on 4. 1. 2025.
//
#include "names.h"

#include <stdlib.h>
#include <string.h>

char * add_suffix(const char * name, const char * suffix) {
    const int name_len = strlen(name);
    const int new_len = name_len + strlen(suffix) + 2;
    char * result = calloc(new_len, sizeof(char));
    strcpy(result, name);
    result[name_len] = '-';
    strcpy(result + name_len + 1, suffix);
    return result;
}

void destroy_names(shared_names * names) {
    free(names->shm_name_);
    free(names->mut_pc_);
    free(names->sem_produce_);
    free(names->sem_consume_);
}