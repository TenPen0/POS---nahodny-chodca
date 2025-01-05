//
// Created by Vladimir on 3. 1. 2025.
//

#include "client.h"

#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../shm/synBuffer.h"
#include "stdio.h"
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void drawBoard(int height, int width, simulationState * simState) {
    for (int x = 0; x < (width*3)+1; x++) {
        printf("-");
    }
    printf("\n");
    for (int y = 0; y < height; y++) {
        printf("|");
        for (int x = 0; x < width; x++) {
            printf("%2d|",simState->tile[x][y]);
        }
        printf("\n");
        for (int x = 0; x < (width*3)+1; x++) {
            printf("-");
        }
        printf("\n");
    }

    printf("\n\n");
}

void drawMenu() {
    printf("Nova Simulacia.............1\n");
    printf("Pripojenie k simulacii.....2\n");
    printf("Opakovat simulaciu.........3\n");
    printf("Koniec.....................4\n");
}

int menuSelect() {
    while (true) {
        char inputBuff[32];
        scanf("%s",&inputBuff);
        if (strlen(inputBuff) == 1) {
            if (isdigit(inputBuff[0])) {
                int choice = atoi(inputBuff);
                if (choice >= 1 && choice <= 4) {
                    return choice;
                }
            }
        }
        printf("Chybna volba, zadaj znova\n");
    }
}

void boardThread(shared_names * names) {

    synBuffer buffer;
    syn_shm_buffer_open(&buffer, names);

    simulationState simState;

    while (true) {
        syn_shm_buffer_pop(&buffer, &simState);
        if (simState.ended) {
            break;
        }
        drawBoard(5,7, &simState);
        usleep(500000);
    }

    syn_shm_buffer_close(&buffer);
}

void startSimulation(shared_names * names, const char * suffix) {
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

    const pid_t pid = fork();

    if (pid < 0) {
        perror("Chyba volania fork!");
        exit(2);
    }

    if (pid == 0) {
        // vykoná detský proces
        const char * args[] = {"./server", suffix, specs, NULL};
        execvp(args[0],args);
        printf("Chyba exec: %s\n", strerror(errno));

    } else {
        // vykoná rodičovský proces
        boardThread(names);
    }
}

void connectToSimulation() {

}



int main(int argc, const char * argv[]) {
    shared_names names;
    names.shm_name_ = add_suffix("SHM", argv[1]);
    names.mut_pc_ = add_suffix("MUT-PC", argv[1]);
    names.sem_produce_ = add_suffix("SEM-P", argv[1]);
    names.sem_consume_ = add_suffix("SEM-C", argv[1]);

    shm_init(&names);
    syn_shm_buffer_init(&names);

    drawMenu();
    int choice = menuSelect();
    switch (choice) {
        case 1:
            startSimulation(&names, argv[1]);
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
    shm_destroy(&names);
    syn_shm_buffer_destroy(&names);


    destroy_names(&names);
}
