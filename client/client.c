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
    printf("Nova Simulacia....................1\n");
    printf("Opakovat simulaciu................2\n");
    printf("Zobrazit vysledok simulacie.......3\n");
    printf("Ovladanie.........................4\n");
    printf("Koniec............................5\n");
}

void startSimulation(const char * suffix, shared_names * inputNames, shared_names * simNames, char * specs) {
    synSimBuffer simBuff;
    syn_shm_sim_buffer_open(&simBuff,simNames);
    syn_shm_sum_buffer_flush(&simBuff);
    syn_shm_sim_buffer_close(&simBuff);

    synInputBuffer inputBuff;
    syn_shm_input_buffer_open(&inputBuff,inputNames);
    syn_shm_input_buffer_flush(&inputBuff);
    syn_shm_input_buffer_close(&inputBuff);

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
        simulationData simData;
        initSimData(&simData, specs);
        drawThreadDataInit(&dData, simNames, &simData);
        pthread_t drawThreadId;
        pthread_create(&drawThreadId, NULL, &drawThread, &dData);

        pthread_join(drawThreadId, NULL);
        pthread_join(inputThreadID, NULL);
        int status;
        wait(&status);
    }
}
int readInt(int min, int max) {
    while (1) {
        char inputBuff[32];
        fgets(inputBuff,sizeof(inputBuff), stdin);
        bool isNumber = true;
        if (strlen(inputBuff) > 1) {
            inputBuff[strlen(inputBuff)-1] = 0;
            for (int i = 0; i < strlen(inputBuff); i++) {
                if (isdigit(inputBuff[i]) == false) {
                    isNumber = false;
                    break;
                }
            }
            if (isNumber) {
                int choice = atoi(inputBuff);
                if (choice >= min && choice <= max) {
                    return choice;
                }
            }
        }
        printf("Chybna volba, zadaj znova\n");
    }
}

#define MAX_REPLICATIONS 1024
#define MAX_STEPS 999
void createSimulation(const char * suffix, shared_names * inputNames, shared_names * simNames) {

    char filePath[128];
    printf("zadaj sirku: ");
    int width = readInt(1, MAX_WIDTH);
    printf("zadaj vysku: ");
    int height = readInt(1, MAX_HEIGHT);
    printf("zadaj pocet replikacii: ");
    int replications = readInt(1, MAX_REPLICATIONS);

    int up = -1;
    int down = -1;
    int left = -1;
    int right = -1;
    while (1) {
        printf("zadaj percentualnu pravdepodobnost pohybu smerom hore: ");
        up = readInt(1, 100);
        printf("zadaj percentualnu pradvepodobnost pohybu smerom dole: ");
        down = up + readInt(1, 100);
        printf("zadaj percentualnu pradvepodobnost pohybu smerom vlavo: ");
        left = down + readInt(1, 100);
        printf("zadaj percentualnu pradvepodobnost pohybu smerom vpravo: ");
        right = left + readInt(1, 100);
        if (right == 100) {
            break;
        }
        printf("zadane hodnoty sa nerovnaju 100%%. Vyskusaj znova.\n");
    }

    printf("zadaj maximalny pocet krokov: ");
    int maxSteps = readInt(1, MAX_STEPS);
    printf("Zadaj nazov subor na ulozenie: ");
    scanf("%s", filePath);

    char * specs = malloc(256);
    sprintf(specs, "%d %d %d %d %d %d %d %d %s", width, height, replications, up, down, left, right, maxSteps, filePath);

    //char specs[]= "5 5 10 25 50 75 100 10 vysledok.txt";

    startSimulation(suffix, inputNames, simNames, specs);
    free(specs);
    specs = NULL;
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
                printf("Toto nie je subor simulacie\n");
                fclose(loadFile);
                loadFile = NULL;
            }
        } else {
            printf("Subor sa nenasiel\n");
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


void showResult(void) {
    FILE * file = NULL;
    while (file == NULL) {
        printf("Zadaj nazov suboru s vysledkom simulacie (alebo stlac Enter pre navrat do menu): \n");
        char path[128];
        fgets(path, sizeof(path),stdin);
        if (path[0] == '\n') {
            return;
        }
        path[strlen(path)-1] = '\0';
        file = fopen(path, "r");
        if (file != NULL) {
            char testString[32];
            fgets(testString, sizeof(testString), file);
            if (strcmp(testString, "Ulozena simulacia\n") != 0) {
                printf("Toto nie je subor simulacie\n");
                fclose(file);
                file = NULL;
            }
        } else {
            printf("Subor sa nenasiel\n");
        }
    }

    int width = -1;
    int height = -1;
    int up = -1;
    int down = -1;
    int left = -1;
    int right = -1;
    int maxSteps = -1;
    int replications = -1;
    int finishedReplications = -1;

    fscanf(file, "%d %d %d %d\n", &width, &height, &replications, &finishedReplications);
    fscanf(file, "%d %d %d %d\n", &up, &down, &left, &right);
    fscanf(file, "%d\n", &maxSteps);

    right -= left;
    left -= down;
    down -= up;

    printf("\nRozmery: %dx%d\n", width, height);
    printf("Pocet replikacii: %d z toho %d dokoncenych\n", replications, finishedReplications);
    printf("Maximalny pocet krokov: %d\n", maxSteps);
    printf("Pohyb vpravo: %d%%\n", right);
    printf("Pohyb vlavo: %d%%\n", left);
    printf("pohyb hore: %d%%\n", up);
    printf("pohyb dole: %d%%\n\n", down);

    printf("Priemerny pocet krokov ku stredu: \n");
    for (int i = 0; i < (height*2)+1; i++) {
        char row[(width*5)+3];
        fgets(row, sizeof(row), file);
        printf("%s", row);
    }
    char tmp[2];
    fgets(tmp, sizeof(tmp), file);
    fgets(tmp, sizeof(tmp), file);
    printf("\nSanca dosiahnutia stredu:\n");
    for (int i = 0; i < (height*2)+1; i++) {
        char row[(width*5)+3];
        fgets(row, sizeof(row), file);
        printf("%s", row);
    }
    fclose(file);
    printf("\n");
}

void controls() {
    printf("Pocas simulacie sa zobrazovaci mod pripina nasledujucimi cislami:\n"
           "1 - sumarny mod, priemer\n"
           "2 - sumarny mod, pravdepodobnost\n"
           "3 - interaktivny mod\n"
           "4 - predcasne ukoncenie simulacie\n\n");
}

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        printf("Chyba parameter suffix pre shared memory\n");
        return 1;
    }

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


    //createSimulation(argv[1],&inputNames,&simNames);
    bool end = false;
    do {
        //setbuf(stdout, 0);
        drawMenu();
        int choice = readInt(1,5);
        switch (choice) {
            case 1:
                createSimulation(argv[1],&inputNames,&simNames);
                break;
            case 2:
                loadSimulation(argv[1],&inputNames,&simNames);
                break;
            case 3:
                showResult();
                break;
            case 4:
                controls();
                break;
            case 5:
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
