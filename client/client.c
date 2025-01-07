//
// Created by Vladimir on 3. 1. 2025.
//

#include "client.h"

#include <ctype.h>
#include <errno.h>

#include "../shm/synBuffer.h"
#include "stdio.h"
#include <sys/wait.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "drawThread.h"
#include "inputThread.h"

void drawMenu() {
    printf("Nova Simulacia.............1\n");
    printf("Pripojenie k simulacii.....2\n");
    printf("Opakovat simulaciu.........3\n");
    printf("Koniec.....................4\n");
}



void startSimulation(const char * suffix) {
    /*int width = -1;
    int height = -1;
    int replications = -1;
    int up = -1;
    int down = -1;
    int left = -1;
    int right = -1;
    int maxSteps = -1;
    char filePath[128];
    printf("zadaj sirku: ");
    scanf("%d", &width);
    printf("zadaj vysku: ");
    scanf("%d", &height);
    printf("zadaj pocet replikacii: ");
    scanf("%d", &replications);
    printf("zadaj percentualnu pravdepodobnost pohybu smerom hore: ");
    scanf("%d", &up);
    printf("zadaj percentualnu pradvepodobnost pohybu smerom dole: ");
    scanf("%d", &down);
    printf("zadaj percentualnu pradvepodobnost pohybu smerom vlavo: ");
    scanf("%d", &left);
    printf("zadaj percentualnu pradvepodobnost pohybu smerom vpravo: ");
    scanf("%d", &right);
    printf("zadaj maximalny pocet krokov: ");
    scanf("%d", &maxSteps);
    printf("Zadaj nazov subor na ulozenie: ");
    scanf("%s", filePath);

    char specs[256];
    sprintf(specs, "%d %d %d %d %d %d %d %d %s", width, height, replications, up, down, left, right, maxSteps, filePath);
*/
    char specs[]= "7 5 10 25 25 25 25 10 vysledok.txt";

    shared_names simNames;
    simNames.shm_name_ = add_suffix("S-SHM", suffix);
    simNames.mut_pc_ = add_suffix("S-MUT-PC", suffix);
    simNames.sem_produce_ = add_suffix("S-SEM-P", suffix);
    simNames.sem_consume_ = add_suffix("S-SEM-C", suffix);
    shm_init(&simNames, sizeof(simBuffer));
    syn_shm_buffer_init(&simNames);

    shared_names inputNames;
    inputNames.shm_name_ = add_suffix("I-SHM", suffix);
    inputNames.mut_pc_ = add_suffix("I-MUT-PC", suffix);
    inputNames.sem_produce_ = add_suffix("I-SEM-P", suffix);
    inputNames.sem_consume_ = add_suffix("I-SEM-C", suffix);
    shm_init(&inputNames, sizeof(inputBuffer));
    syn_shm_buffer_init(&inputNames);


    const pid_t pid = fork();

    if (pid < 0) {
        perror("Chyba volania fork!");
        exit(2);
    }

    if (pid == 0) {
        //detský proces - server
        char * args[] = {"./server", suffix, specs, NULL};
        execvp(args[0],args);
        printf("Chyba exec: %s\n", strerror(errno));

    } else {
        //rodičovský proces - client

        inputThreadData iData;
        inputThreadInit(&iData, &inputNames, &simNames);
        pthread_t inputThreadID;
        pthread_create(&inputThreadID, NULL, &inputThread, &iData);

        drawThreadData dData;
        drawThreadDataInit(&dData, &simNames);
        pthread_t drawThreadId;
        pthread_create(&drawThreadId, NULL, &drawThread, &dData);

        pthread_join(drawThreadId, NULL);
        pthread_cancel(inputThreadID);
        int status;
        wait(&status);

        shm_destroy(&simNames);
        syn_shm_buffer_destroy(&simNames);
        shm_destroy(&inputNames);
        syn_shm_buffer_destroy(&inputNames);

        destroy_names(&inputNames);
        destroy_names(&simNames);
    }


}

void connectToSimulation() {

}



int main(int argc, const char * argv[]) {


    drawMenu();
    int choice = readInt(1,4);
    switch (choice) {
        case 1:
            startSimulation(argv[1]);
            break;
        case 2:
            connectToSimulation();
            break;
        default:
            perror("input error");
            exit(EXIT_FAILURE);
    }


    int status;
    wait(&status);
}
