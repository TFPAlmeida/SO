//
// Created by tiago on 31/05/2022.
//

#include "threads.h"

#define THREADS_NUM 2
#define COLUMNS 5

char path_1_[100] = "C:\\Users\\tiago\\CLionProjects\\SO\\Data\\INFO_TXT.txt";
char *salas_3_[] = {"sala_triagem", "triagem", "sala_de_espera", "consulta"};

int** arr;
int lines;
//pthread_mutex_t mutexWorker;
int contador = 0;
/*
void *threads_ocupacao(void *parameters){
    pthread_mutex_lock(&mutexWorker);
    int index = *(int*) parameters;
    ocupacao_das_salas_3_(index);
    printf("Id: %d, contador: %d\n",index,contador);
    contador = 0;
    pthread_mutex_unlock(&mutexWorker);
}*/

int main_threads(int argc, char *argv[]) {


    /******************************************************************************************************************/
    char nameficheiro[] = "C:\\Users\\tiago\\CLionProjects\\SO\\Data\\all_timestamps.csv";
    int t_ficheiro = tamanho_do_ficheiro_3_(nameficheiro);
    lines = t_ficheiro;
    arr = (int**) malloc(lines * sizeof(int*));
    for (int index=0;index<lines;++index)
    {
        arr[index] = (int*)malloc(5 * sizeof(int));
    }

    ler_ficheiro_3_();
    //print_timestamps_3_();
    /******************************************************************************************************************/
    /*pthread_t th[THREADS_NUM];
    pthread_mutex_init(&mutexWorker);
    for(int i = 1; i <= THREADS_NUM; i++){
        int * a = malloc(sizeof(int));
        *a = i;
        if(pthread_create(&th[i],NULL,&threads_ocupacao, a) != 0){
            perror("Failed to create thread!");
        }
    }

    for(int i = 1; i <= THREADS_NUM; i++){
        if(pthread_join(th[i], NULL) != 0){
            perror("Failed to join thread!");
        }
    }
     pthread_mutex_destroy(&mutexWorker);
     */
    /******************************************************************************************************************/

    return 0;
}

int tamanho_do_ficheiro_3_(char nameficheiro[]) {
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


void ler_ficheiro_3_() {
    FILE *file;
    file = fopen("C:\\Users\\tiago\\CLionProjects\\SO\\Data\\all_timestamps.csv", "r");

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

void ocupacao_das_salas_3_(int n) {
    int size = lines / THREADS_NUM;
    int size_process_child = size * n;
    int x1 = 0, timestamps;
    int ocupacao[4] = {0, 0, 0, 0};
    if (n == THREADS_NUM && lines % 2 != 0) {
        size_process_child++;
    }

    if (n != 1) {
        x1 = size * (n - 1);
    }


    for (int x = x1; x < size_process_child; x++) {
        for (int z = 0; z < COLUMNS; z++) {
            timestamps = *(*(arr + x) + z);
            contador++;
            for (int y = x1; y < size_process_child; y++) {

                if (*(*(arr + y) + 0) < timestamps < *(*(arr + y) + 1)) {
                    ocupacao[0]++;
                }
                if (*(*(arr + y) + 1) < timestamps < *(*(arr + y) + 2)) {
                    ocupacao[1]++;
                }
                if (*(*(arr + y) + 3) < timestamps < *(*(arr + y) + 4)) {
                    ocupacao[2]++;
                }
                if (*(*(arr + y) + 4) < timestamps < *(*(arr + y) + 5)) {
                    ocupacao[3]++;
                }

            }
            escrever_ficheiro_3_(timestamps, ocupacao);
            for(int i = 0; i < 4; i++){
                ocupacao[i]=0;
            }
        }


    }

}

void escrever_ficheiro_3_(int timestamps, int ocupacao[4]) {
    int fd = open(path_1_, O_WRONLY | O_APPEND | O_CREAT, 0744);

    if (fd == -1) {
        perror("File open");
        exit(1);
    }

    char *buf = (char *) malloc(sizeof(char) * 1000000);

    for (int i = 0; i < 4; i++) {
        printf("%d",i);
        sprintf(buf, "id: %d | timestamp: %d | sala: %s | ocupacao: %d", getpid(), timestamps, *(salas_3_ + i),
                ocupacao[i]);
        strcat(buf, "\n");
    }

    strcat(buf, "\n");
    write(fd, buf, strlen(buf));


    close(fd);
    free(buf);
}

void print_timestamps_3_() {

    for(int x = 0; x < lines; x++){
        for(int y = 0; y < COLUMNS; y++){
            printf("%d ", *(*(arr + x) + y));
        }
        printf("\n");
    }

}