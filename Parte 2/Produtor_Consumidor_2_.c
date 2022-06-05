//
// Created by tiago on 05/06/2022.
//

#include "Produtor_Consumidor_2_.h"


#define THREADS_Produtor 2
#define THREADS_Consumidor 2
#define COLUMNS 5
struct tm *mytime;
char path_3_[100] = "C:\\Users\\tiago\\CLionProjects\\SO\\Data\\INFO_THREADS_PC_TXT.txt";

int **arr;
int **produto;
int lines;
int x1 = 0;
int size_process_child = 0;
int timestamps;
/*
pthread_mutex_t trincop, trincoc;
sem_t pode_prod, pode_cons;


void *Produtor2(void *parameters) {
    while (1){
        sem_wait(&pode_prod);
        pthread_mutex_lock(&trinco_p);
        int index = *(int*) parameters;
        ocupacao_das_salas_4_(index);
        pthread_mutex_unlock(&trinco_p);
        sem_post(&pode_cons);
    }
}

void *Consumidor2(void *parameters) {
    while(1)
    {
        sem_wait(&pode_cons);
        pthread_mutex_lock(&trinco_c);
        escrever_ficheiro_4_();
        pthread_mutex_unlock(&trinco_c);
        sem_post(&pode_prod);
    }
}*/

int main_PC2(int argc, char *argv[]) {


    /******************************************************************************************************************/
    char nameficheiro[] = "C:\\Users\\tiago\\CLionProjects\\SO\\Data\\all_timestamps.csv";
    int t_ficheiro = tamanho_do_ficheiro_4_(nameficheiro);
    lines = t_ficheiro;
    TH_DATA * TD = calloc(lines, sizeof(int));
    arr = (int **) malloc(lines * sizeof(int *));
    for (int index = 0; index < lines; ++index) {
        arr[index] = (int *) malloc(5 * sizeof(int));
    }

    produto = (int **) malloc(lines * sizeof(int *));
    for (int index = 0; index < lines; ++index) {
        produto[index] = (int *) malloc(5 * sizeof(int));
    }

    ler_ficheiro_4_();
    //print_timestamps_4_();
    /******************************************************************************************************************/
    /* pthread_t thP[THREADS_Produtor], thC[THREADS_Consumidor];
     pthread_mutex_init(&mutex);
     sem_init(&pode_prod, 0, 1);
     sem_init(&pode_cons, 0, 1);
     for (int i = 1; i <= THREADS_Produtor; i++) {
         if (pthread_create(&thP[i], NULL, &threads_ocupacao, NULL) != 0) {
             perror("Failed to create thread Produtor!");
         }
     }
     for (int i = 0; i < THREADS_Consumidor; i++) {
         if (pthread_create(&thC[i], NULL, &threads_ocupacao, NULL) != 0) {
             perror("Failed to create thread Consumidor!");
         }
     }

     for (int i = 1; i <= THREADS_Produtor; i++) {
         if (pthread_join(thP[i], NULL) != 0) {
             perror("Failed to join thread Produtor!");
         }
     }

     for (int i = 0; i < THREADS_Consumidor; i++) {
         if (pthread_join(thC[i], NULL) != 0) {
             perror("Failed to join thread Consumidor!");
         }
     }
     pthread_mutex_destroy(&mutexWorker);
     sem_destroy(&pode_prod);
     sem_destroy(&pode_cons);*/


    /******************************************************************************************************************/

    return 0;
}

int tamanho_do_ficheiro_5_(char nameficheiro[]) {
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

void ler_ficheiro_5_() {
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

void ocupacao_das_salas_5_(int n) {
    int size = lines / THREADS_Produtor;
    size_process_child = size * n;

    int ocupacao[4] = {0, 0, 0, 0};
    if (n == THREADS_Produtor && lines % 2 != 0) {
        size_process_child++;
    }

    if (n != 1) {
        x1 = size * (n - 1);
    }


    for (int x = x1; x < size_process_child; x++) {
        timestamps = *(*(arr + x) + 0);
        for (int y = x1; y < size_process_child; y++) {
            if (*(*(arr + y) + 0) < timestamps < *(*(arr + y) + 1)) {
                ocupacao[0]++;
            }
            if (*(*(arr + y) + 1) < timestamps < *(*(arr + y) + 2)) {
                ocupacao[1]++;
            }
            if (*(*(arr + y) + 2) < timestamps < *(*(arr + y) + 3)) {
                ocupacao[2]++;
            }
            if (*(*(arr + y) + 3) < timestamps < *(*(arr + y) + 4)) {
                ocupacao[3]++;
            }
        }
        *(*(produto + x) + 0) = timestamps;
        *(*(produto + x) + 1) = ocupacao[0];
        *(*(produto + x) + 2) = ocupacao[1];
        *(*(produto + x) + 3) = ocupacao[2];
        *(*(produto + x) + 4) = ocupacao[3];
        for (int i = 0; i < 4; i++) {
            ocupacao[i] = 0;
        }
    }

}

void escrever_ficheiro_5_() {
    time_t currentTime;
    int ano = 0;

    for (int x = 0; x < lines; x++) {
        for (int y = 0; y < COLUMNS; y++) {
            currentTime = timestamps;
            mytime = localtime(&currentTime);
            ano = mytime->tm_year + 1900;
        }
    }
    char s[1024];
    sprintf(s,"C:\\Users\\tiago\\CLionProjects\\SO\\Data\\output-%d.txt",ano);
    int fd = open(s, O_WRONLY | O_APPEND | O_CREAT, 0744);

    if (fd == -1) {
        perror("File open");
        exit(1);
    }

    char *buf = (char *) malloc(sizeof(char) * 1000000);

    for (int x = x1; x < size_process_child; x++){
        for(int y = 0; y < 5; y++){
            sprintf(buf, "%d    ", *(*(produto + x) + y));
        }
        strcat(buf, "\n");
    }

    strcat(buf, "\n");
    write(fd, buf, strlen(buf));


    close(fd);
    free(buf);

}

void print_timestamps_5_() {

    for (int x = 0; x < lines; x++) {
        for (int y = 0; y < COLUMNS; y++) {
            printf("%d ", *(*(produto + x) + y));
        }
        printf("\n");
    }

}