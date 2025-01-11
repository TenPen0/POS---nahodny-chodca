//
// Created by Vladimir on 10. 1. 2025.
//

#ifndef MENU_H
#define MENU_H

#include "../shm/names.h"

#define MAX_REPLICATIONS 1024
#define MAX_STEPS 999

int readInt(int min, int max);
void drawMenu();
void startSimulation(const char * suffix, sharedNames * inputNames, sharedNames * simNames, char * specs);
void newSimulation(const char * suffix, sharedNames * inputNames, sharedNames * simNames);
void loadSimulation(const char * suffix, sharedNames * inputNames, sharedNames * simNames);
void showResult();
void controls();

#endif //MENU_H
