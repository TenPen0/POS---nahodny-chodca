//
// Created by Vladimir on 2. 1. 2025.
//

#ifndef NAMES_H
#define NAMES_H

typedef struct sharedNames {
    char *shmName;
    char *mut;
    char *semProduce;
    char *semConsume;
} sharedNames;

char * addSuffix(const char * name, const char * suffix);
void destroyNames(sharedNames * names);
#endif //NAMES_H
