//
// Created by tiago on 31/03/2022.
//

#include "pipes.h"

#define SIZE 10000
#define PROCESS_NUM 2


char *salas[] = {"sala_triagem", "triagem", "sala_de_espera", "consulta"};

int main_pipes(int argc, char *argv[]) {


    /******************************************************************************************************************/
    char nameficheiro[] = "C:\\Users\\tiago\\CLionProjects\\SO\\all_timestamps.csv";
    DYNARRAY_TIMESTAMPS_1_ dt = {0, 0};
    int t_ficheiro = tamanho_do_ficheiro_1_(nameficheiro);
    int lines = t_ficheiro;
    create_lista_timestamps_1_(&dt, lines);
    ler_ficheiro_1_(&dt, lines);
    print_timestamps_1_(&dt, lines);
    char buffer[SIZE];
    /******************************************************************************************************************/
    int pids[PROCESS_NUM];
    int fd[2];

    for (int i = 0; i < PROCESS_NUM; i++) {
        if (pipe(fd) == -1) {
            perror("Error with creating pipe\n");
        }
    }
    for (int i = 1; i <= PROCESS_NUM; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("Error with creating process\n");
        }
        if (pids[i] == 0) {
            //Child Process
            close(fd[0]);
            ocupacao_das_salas_1_(&dt, lines, i, fd);
            close(fd[1]);
            exit(0);
        }
    }
    //Main Process

    int ocupacao_2_[4], id_2_, timestamps_2_;
    char *salas_2_[4];
    int ficheiro = open("C:\\Users\\tiago\\CLionProjects\\SO\\pipe.txt", O_WRONLY|O_APPEND|O_CREAT, 0666);
    close(fd[1]);
    dup(ficheiro);
    ssize_t n;
    while ((n = readn(fd[0], buffer, SIZE)) > 0)   // pai vai ler do pipe
    {
        write(ficheiro, buffer, sizeof(buffer));
    }
    close(fd[0]);

    wait(NULL);


    /******************************************************************************************************************/
    return 0;
}

int tamanho_do_ficheiro_1_(char nameficheiro[]) {
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

void create_lista_timestamps_1_(DYNARRAY_TIMESTAMPS_1_ *dynarrayTimestamps, int size) {
    dynarrayTimestamps->timestamp = malloc(size * sizeof(TIMESTAMP_1_));
    dynarrayTimestamps->n_timestamps = size;
    dynarrayTimestamps->currentadmissao = 0;
}

void ler_ficheiro_1_(DYNARRAY_TIMESTAMPS_1_ *dynarrayTimestamps, int lines) {
    FILE *file;
    file = fopen("C:\\Users\\tiago\\CLionProjects\\SO\\all_timestamps.csv", "r");

    char admissao[11], inicio_triagem[11], fim_triagem[11], inicio_medico[11], fim_medico[11], line[100];
    char *delim = ";";
    char *delim2 = "\n";

    if (file == NULL) {
        printf("Nao foi possivel abrir o ficheiro\n");

    }

    while (fgets(line, sizeof(line), (FILE *) file) != NULL) {
        TIMESTAMP_1_ *t = dynarrayTimestamps->timestamp + dynarrayTimestamps->currentadmissao;
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

void ocupacao_das_salas_1_(DYNARRAY_TIMESTAMPS_1_ *dynarrayTimestamps, int lines, int n, int fd[2]) {
    int size = lines / PROCESS_NUM;
    int size_process_child = size * n;
    int x1 = 0, timestamps[5], times, id = getpid();
    int ocupacao[4] = {0, 0, 0, 0};
    char *buf = (char *) malloc(sizeof(char) * 1000000);
    if (n == PROCESS_NUM && lines % 2 != 0) {
        size_process_child++;
    }

    if (n != 1) {
        x1 = size * (n - 1);
    }


    for (int x = x1; x < size_process_child; x++) {

        TIMESTAMP_1_ *t1 = dynarrayTimestamps->timestamp + x;
        timestamps[0] = t1->admissao;
        timestamps[1] = t1->inicio_triagem;
        timestamps[2] = t1->fim_triagem;
        timestamps[3] = t1->inicio_medico;
        timestamps[4] = t1->fim_medico;
        for (int z = 0; z < COLUMNS; z++) {
            for (int y = x1; y < size_process_child; y++) {
                TIMESTAMP_1_ *t2 = dynarrayTimestamps->timestamp + y;
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

            for (int i = 0; i < 4; i++) {
                sprintf(buf, "#PID:%d |%d | %s | %d", id, times, *(salas + i), ocupacao[i]);
                strcat(buf, "\n");
                writen(fds[1], buf, strlen(buf));
                ocupacao[i] = 0;
            }
        }
    }
}

void print_timestamps_1_(DYNARRAY_TIMESTAMPS_1_ *dynarrayTimestamps, int lines) {

    TIMESTAMP_1_ *t = dynarrayTimestamps->timestamp;
    int size = dynarrayTimestamps->n_timestamps;
    for (int x = 0; x < size; x++) {
        printf("%d %d %d %d %d\n", t->admissao, t->inicio_triagem, t->fim_triagem, t->inicio_medico, t->fim_medico);
        t++;
    }

}

