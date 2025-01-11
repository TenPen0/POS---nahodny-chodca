//
// Created by Vladimir on 4. 1. 2025.
//
#include "names.h"

#include <stdlib.h>
#include <string.h>

char * addSuffix(const char * name, const char * suffix) {
    const int name_len = strlen(name);
    const int new_len = name_len + strlen(suffix) + 2;
    char * result = calloc(new_len, sizeof(char));
    strcpy(result, name);
    result[name_len] = '-';
    strcpy(result + name_len + 1, suffix);
    return result;
}

void destroyNames(sharedNames * names) {
    free(names->shmName);
    free(names->mut);
    free(names->semProduce);
    free(names->semConsume);
}