//
// Created by tiago on 31/03/2022.
//

#include "process.h"

#define PROCESS_NUM 2

char path[100] = "C:\\Users\\tiago\\CLionProjects\\SO\\INFO_TXT.txt";
char *salas[] = {"sala_triagem", "triagem", "sala_de_espera", "consulta"};

int main_process(int argc, char *argv[]) {


    /******************************************************************************************************************/
    char nameficheiro[] = "C:\\Users\\tiago\\CLionProjects\\SO\\all_timestamps.csv";
    int t_ficheiro = tamanho_do_ficheiro(nameficheiro);
    int lines = t_ficheiro;
    int** arr = (int**)malloc(lines * sizeof(int*));
    for (int index=0;index<lines;++index)
    {
        arr[index] = (int*)malloc(5 * sizeof(int));
    }

    ler_ficheiro(arr, lines);
    print_timestamps(arr, lines);
    /******************************************************************************************************************/
    /*int pids[PROCESS_NUM];

    for (int i = 1; i <= PROCESS_NUM; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("Error with creating process\n");
        }
        if (pids[i] == 0) {
            //Child Process
            ocupacao_das_salas(arr, lines, i, path);
            exit(0);
        }
    }
    //Main Process
    for (int i = 0; i < PROCESS_NUM; i++) {
        wait(NULL);
    }*/
    /******************************************************************************************************************/

    return 0;
}

int tamanho_do_ficheiro(char nameficheiro[]) {
    int count = 0;
    FILE *fp;
    fp = fopen(nameficheiro, "r");

    if (fp == NULL) {
        perror("Nao foi possivel ler o ficheiro!\n");
    }

    char c;

    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            count++;
        }
    }
    fclose(fp);

    return count;
}


void ler_ficheiro(int** arr, int lines) {
    FILE *file;
    file = fopen("C:\\Users\\tiago\\CLionProjects\\SO\\all_timestamps.csv", "r");

    char admissao[11], inicio_triagem[11], fim_triagem[11], inicio_medico[11], fim_medico[11], line[100];
    char *delim = ";";
    char *delim2 = "\n";

    if (file == NULL) {
        printf("Nao foi possivel abrir o ficheiro\n");

    }

    int i = 0;
    while (fgets(line, sizeof(line), (FILE *) file) != NULL) {

        strcpy(admissao, strtok(line, delim));
        strcpy(inicio_triagem, strtok(NULL, delim));
        strcpy(fim_triagem, strtok(NULL, delim));
        strcpy(inicio_medico, strtok(NULL, delim));
        strcpy(fim_medico, strtok(NULL, delim2));

        *(*(arr + i) + 0) = atoi(admissao);
        *(*(arr + i) + 1) = atoi(inicio_triagem);
        *(*(arr + i) + 2) = atoi(fim_triagem);
        *(*(arr + i) + 3) = atoi(inicio_medico);
        *(*(arr + i) + 4) = atoi(fim_medico);
       i++;
    }
}

void ocupacao_das_salas(int** arr, int lines, int n) {
    int size = lines / PROCESS_NUM;
    int size_process_child = size * n;
    int x1 = 0, timestamps;
    int ocupacao[4] = {0, 0, 0, 0};
    if (n == PROCESS_NUM && lines % 2 != 0) {
        size_process_child++;
    }

    if (n != 1) {
        x1 = size * (n - 1);
    }


    for (int x = x1; x < size_process_child; x++) {
        for (int z = 0; z < COLUMNS; z++) {
            timestamps = *(*(arr + x) + z);
            for (int y = x1; y < size_process_child; y++) {

                if (*(*(arr + y) + 0) < timestamps < *(*(arr + y) + 0)) {
                    ocupacao[0]++;
                }
                if (*(*(arr + y) + 0) < timestamps < *(*(arr + y) + 0)) {
                    ocupacao[1]++;
                }
                if (*(*(arr + y) + 0) < timestamps < *(*(arr + y) + 0)) {
                    ocupacao[2]++;
                }
                if (*(*(arr + y) + 0) < timestamps < *(*(arr + y) + 0)) {
                    ocupacao[3]++;
                }
            }

            escrever_ficheiro(path,timestamps, ocupacao);
            for(int i = 0; i < 4; i++){
                ocupacao[i]=0;
            }
        }


    }

}

void escrever_ficheiro(char *path1, int timestamps, int ocupacao[4]) {
    int fd = open(path1, O_WRONLY | O_APPEND | O_CREAT, 0744);

    if (fd == -1) {
        perror("File open");
        exit(1);
    }

    char *buf = (char *) malloc(sizeof(char) * 1000000);

    for (int i = 0; i < 4; i++) {
        printf("%d",i);
        sprintf(buf, "id: %d | timestamp: %d | sala: %s | ocupacao: %d", getpid(), timestamps, *(salas + i),
                ocupacao[i]);
        strcat(buf, "\n");
    }

    strcat(buf, "\n");
    write(fd, buf, strlen(buf));


    close(fd);
    free(buf);
}

void print_timestamps(int** arr, int lines) {

    for(int x = 0; x < lines; x++){
        for(int y = 0; y < COLUMNS; y++){
            printf("%d ", *(*(arr + x) + y));
        }
        printf("\n");
    }

}

