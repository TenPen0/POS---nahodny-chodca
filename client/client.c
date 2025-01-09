//
// Created by Vladimir on 3. 1. 2025.
//

#include "client.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>

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

void startSimulation(const char * suffix, shared_names * inputNames, shared_names * simNames, char * specs) {
    synSimBuffer simBuff;
    syn_shm_sim_buffer_open(&simBuff,simNames);
    syn_shm_sum_buffer_flush(&simBuff);
    syn_shm_sim_buffer_close(&simBuff);



    const pid_t pid = fork();

    if (pid < 0) {
        perror("Chyba volania fork!");
        exit(2);
    }

    if (pid == 0) {
        //detský proces - server
        const char * args[] = {"./server", suffix, specs, NULL};
        execvp(args[0],args);
        printf("Chyba exec: %s\n", strerror(errno));

    } else {
        //rodičovský proces - client

        inputThreadData iData;
        inputThreadInit(&iData, inputNames, simNames);
        pthread_t inputThreadID;
        pthread_create(&inputThreadID, NULL, &inputThread, &iData);

        drawThreadData dData;
        drawThreadDataInit(&dData, simNames);
        pthread_t drawThreadId;
        pthread_create(&drawThreadId, NULL, &drawThread, &dData);

        pthread_join(drawThreadId, NULL);
        pthread_join(inputThreadID, NULL);
        int status;
        wait(&status);
    }
}

void createSimulation(const char * suffix, shared_names * inputNames, shared_names * simNames) {
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

    char * specs = malloc(256);
    sprintf(specs, "%d %d %d %d %d %d %d %d %s", width, height, replications, up, down, left, right, maxSteps, filePath);
*/
    char specs[]= "5 5 10 25 50 75 100 10 vysledok.txt";

    startSimulation(suffix, inputNames, simNames, specs);
    /*free(specs);
    specs = NULL;*/
}




void loadSimulation(const char * suffix, shared_names * inputNames, shared_names * simNames) {
    FILE * loadFile = NULL;
    FILE * saveFile = NULL;
    char savePath[128];

    while (loadFile == NULL) {
        printf("Zadaj nazov suboru na nacitanie (alebo stlac Enter pre navrat do menu): \n");
        char loadPath[128];
        fgets(loadPath, sizeof(loadPath),stdin);
        if (loadPath[0] == '\n') {
            return;
        }
        loadPath[strlen(loadPath)-1] = '\0';
        loadFile = fopen(loadPath, "r");
        if (loadFile != NULL) {
            char testString[32];
            fgets(testString, sizeof(testString), loadFile);
            if (strcmp(testString, "Ulozena simulacia\n") != 0) {
                printf("Toto nie je subor simulacie");
                fclose(loadFile);
            }
        } else {
            printf("Subor sa nenasiel");
        }
    }
    printf("Zadaj pocet replikacii: \n");
    int replications = readInt(1, INT_MAX);
    while (saveFile == NULL) {
        printf("Zadaj nazov suboru na ulozenie: \n");
        fgets(savePath, sizeof(savePath),stdin);
        savePath[strlen(savePath)-1] = '\0';
        saveFile = fopen(savePath, "a");
    }
    fclose(saveFile);

    int width = -1;
    int height = -1;
    int up = -1;
    int down = -1;
    int left = -1;
    int right = -1;
    int maxSteps = -1;
    int tmp;

    fscanf(loadFile, "%d %d %d %d", &width, &height, &tmp, &tmp);
    fscanf(loadFile, "%d %d %d %d", &up, &down, &left, &right);
    fscanf(loadFile, "%d", &maxSteps);
    fclose(loadFile);

    char * specs = malloc(256);
    sprintf(specs, "%d %d %d %d %d %d %d %d %s", width, height, replications, up, down, left, right, maxSteps, savePath);
    startSimulation(suffix, inputNames, simNames, specs);
    free(specs);
    specs = NULL;
}



int main(int argc, const char * argv[]) {

    shared_names simNames;
    simNames.shm_name_ = add_suffix("S-SHM", argv[1]);
    simNames.mut_pc_ = add_suffix("S-MUT-PC", argv[1]);
    simNames.sem_produce_ = add_suffix("S-SEM-P", argv[1]);
    simNames.sem_consume_ = add_suffix("S-SEM-C", argv[1]);

    sem_t *mut_pc, *sem_produce, *sem_consume;
    sem_t *mut_pc2, *sem_produce2, *sem_consume2;

    shm_sim_init(&simNames);
    syn_shm_buffer_init(&simNames, &mut_pc, &sem_produce, &sem_consume);

    shared_names inputNames;
    inputNames.shm_name_ = add_suffix("I-SHM", argv[1]);
    inputNames.mut_pc_ = add_suffix("I-MUT-PC", argv[1]);
    inputNames.sem_produce_ = add_suffix("I-SEM-P", argv[1]);
    inputNames.sem_consume_ = add_suffix("I-SEM-C", argv[1]);
    shm_input_init(&inputNames);
    syn_shm_buffer_init(&inputNames, &mut_pc2, &sem_produce2, &sem_consume2);

    createSimulation(argv[1],&inputNames,&simNames);
    bool end = false;
    do {
        setbuf(stdout, 0);
        drawMenu();
        int choice = readInt(1,4);
        switch (choice) {
            case 1:
                createSimulation(argv[1],&inputNames,&simNames);
                break;
            case 2:
                loadSimulation(argv[1],&inputNames,&simNames);
                break;
            case 3:
                end = true;
                break;
            default:
                break;
        }
    } while (!end);

    int status;
    wait(&status);


    syn_shm_buffer_destroy(&simNames, mut_pc, sem_produce, sem_consume);
    shm_destroy(&simNames);

    syn_shm_buffer_destroy(&inputNames, mut_pc2, sem_produce2, sem_consume2);
    shm_destroy(&inputNames);

    destroy_names(&inputNames);
    destroy_names(&simNames);
}
