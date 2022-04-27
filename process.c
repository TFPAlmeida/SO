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
    DYNARRAY_TIMESTAMPS dt = {0, 0};
    int t_ficheiro = tamanho_do_ficheiro(nameficheiro);
    int lines = t_ficheiro;
    create_lista_timestamps(&dt, lines);
    ler_ficheiro(&dt, lines);
    print_timestamps(&dt, lines);
    /******************************************************************************************************************/
    /*int pids[PROCESS_NUM];

    for (int i = 1; i <= PROCESS_NUM; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("Error with creating process\n");
        }
        if (pids[i] == 0) {
            //Child Process
            ocupacao_das_salas(&dt, lines, i, path);
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

void create_lista_timestamps(DYNARRAY_TIMESTAMPS *dynarrayTimestamps, int size) {
    dynarrayTimestamps->timestamp = malloc(size * sizeof(TIMESTAMP));
    dynarrayTimestamps->n_timestamps = size;
    dynarrayTimestamps->currentadmissao = 0;
}

void ler_ficheiro(DYNARRAY_TIMESTAMPS *dynarrayTimestamps, int lines) {
    FILE *file;
    file = fopen("C:\\Users\\tiago\\CLionProjects\\SO\\all_timestamps.csv", "r");

    char admissao[11], inicio_triagem[11], fim_triagem[11], inicio_medico[11], fim_medico[11], line[100];
    char *delim = ";";
    char *delim2 = "\n";

    if (file == NULL) {
        printf("Nao foi possivel abrir o ficheiro\n");

    }

    while (fgets(line, sizeof(line), (FILE *) file) != NULL) {
        TIMESTAMP *t = dynarrayTimestamps->timestamp + dynarrayTimestamps->currentadmissao;
        strcpy(admissao, strtok(line, delim));
        strcpy(inicio_triagem, strtok(NULL, delim));
        strcpy(fim_triagem, strtok(NULL, delim));
        strcpy(inicio_medico, strtok(NULL, delim));
        strcpy(fim_medico, strtok(NULL, delim2));

        t->admissao = atoi(admissao);
        t->inicio_triagem = atoi(inicio_triagem);
        t->fim_triagem = atoi(fim_triagem);
        t->inicio_medico = atoi(inicio_medico);
        t->fim_medico = atoi(fim_medico);
        dynarrayTimestamps->currentadmissao++;
    }
}

void ocupacao_das_salas(DYNARRAY_TIMESTAMPS *dynarrayTimestamps, int lines, int n) {
    int size = lines / PROCESS_NUM;
    int size_process_child = size * n;
    int x1 = 0, timestamps[5], times;
    int ocupacao[4] = {0, 0, 0, 0};
    if (n == PROCESS_NUM && lines % 2 != 0) {
        size_process_child++;
    }

    if (n != 1) {
        x1 = size * (n - 1);
    }


    for (int x = x1; x < size_process_child; x++) {

        TIMESTAMP *t1 = dynarrayTimestamps->timestamp + x;
        timestamps[0] = t1->admissao;
        timestamps[1] = t1->inicio_triagem;
        timestamps[2] = t1->fim_triagem;
        timestamps[3] = t1->inicio_medico;
        timestamps[4] = t1->fim_medico;
        for (int z = 0; z < COLUMNS; z++) {
            for (int y = x1; y < size_process_child; y++) {
                TIMESTAMP *t2 = dynarrayTimestamps->timestamp + y;
                if (t2->admissao < timestamps[z] < t2->inicio_triagem) {
                    ocupacao[0]++;
                }
                if (t2->inicio_triagem < timestamps[z] < t2->fim_triagem) {
                    ocupacao[1]++;
                }
                if (t2->fim_triagem < timestamps[z] < t2->inicio_medico) {
                    ocupacao[2]++;
                }
                if (t2->inicio_medico < timestamps[z] < t2->fim_medico) {
                    ocupacao[3]++;
                }
            }
            times = timestamps[z];
            escrever_ficheiro(path,times, ocupacao);
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

void print_timestamps(DYNARRAY_TIMESTAMPS *dynarrayTimestamps, int lines) {

    TIMESTAMP *t = dynarrayTimestamps->timestamp;
    int size = dynarrayTimestamps->n_timestamps;
    for (int x = 0; x < size; x++) {
        printf("%d %d %d %d %d\n", t->admissao, t->inicio_triagem, t->fim_triagem, t->inicio_medico, t->fim_medico);
        t++;
    }

}

