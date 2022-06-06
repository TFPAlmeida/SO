//
// Created by tiago on 05/06/2022.
//

#include "Produtor_Consumidor_2_.h"


#define THREADS_Produtor 2
#define THREADS_Consumidor 2
#define COLUMNS 5
struct tm *mytime;

int **arr;
int lines;
int x1 = 0;
int size_process_child = 0;
int q = 1;

/*
pthread_mutex_t trincop, trincoc;
sem_t pode_prod, pode_cons;


void *Produtor2(void *parameters) {

    while (1) {
        sem_wait(&pode_prod);
        pthread_mutex_lock(&trinco_p);
        DYNARRAY_TIMESTAMPS *lt = (DYNARRAY_TIMESTAMPS *) parameters;
        ocupacao_das_salas_4_(lt, q);
        q++;
        pthread_mutex_unlock(&trinco_p);
        sem_post(&pode_cons);
    }
}

void *Consumidor2(void *parameters) {

    while (1) {
        {
            sem_wait(&pode_cons);
            pthread_mutex_lock(&trinco_c);
            DYNARRAY_TIMESTAMPS *lt = (DYNARRAY_TIMESTAMPS *) parameters;
            escrever_ficheiro_4_(lt);
            pthread_mutex_unlock(&trinco_c);
            sem_post(&pode_prod);
        }
    }
*/
int main_PC2(int argc, char *argv[]) {


    /******************************************************************************************************************/
    char nameficheiro[] = "C:\\Users\\tiago\\CLionProjects\\SO\\Data\\all_timestamps.csv";
    int t_ficheiro = tamanho_do_ficheiro_5_(nameficheiro);
    lines = t_ficheiro;
    DYNARRAY_TIMESTAMPS lt = {0, 0};
    lt.timestamp = malloc(lines * sizeof(TIMESTAMP));
    lt.currentadmissao = 0;

    arr = (int **) malloc(lines * sizeof(int *));
    for (int index = 0; index < lines; ++index) {
        arr[index] = (int *) malloc(5 * sizeof(int));
    }

    ler_ficheiro_5_();
    /******************************************************************************************************************/
    /* pthread_t thP[THREADS_Produtor], thC[THREADS_Consumidor];
     pthread_mutex_init(&mutex);
     sem_init(&pode_prod, 0, 1);
     sem_init(&pode_cons, 0, 1);
     for (int i = 1; i <= THREADS_Produtor; i++) {
         if (pthread_create(&thP[i], NULL, &Produtor2, &lt) != 0) {
             perror("Failed to create thread Produtor!");
         }
     }
     for (int i = 0; i < THREADS_Consumidor; i++) {
         if (pthread_create(&thC[i], NULL, &Consumidor2, &lt) != 0) {
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

void ocupacao_das_salas_5_(DYNARRAY_TIMESTAMPS *dynarrayTimestamps, int n) {
    int size = lines / THREADS_Produtor;
    size_process_child = size * n;
    int timestamps;
    int ocupacao[4] = {0, 0, 0, 0};

    TIMESTAMP *t = dynarrayTimestamps->timestamp + x1;
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
        t->admissao = timestamps;
        t->ocupacaoET = ocupacao[0];
        t->ocupacaoT = ocupacao[1];
        t->ocupacaoSE = ocupacao[2];
        t->ocupacaoC = ocupacao[3];
        t++;
        dynarrayTimestamps->currentadmissao++;
        for (int i = 0; i < 4; i++) {
            ocupacao[i] = 0;
        }
    }

}

void escrever_ficheiro_5_(DYNARRAY_TIMESTAMPS *dynarrayTimestamps) {
    time_t currentTime;
    int ano = 0;
    char s[1024];
    int fd;

    char *buf = (char *) malloc(sizeof(char) * 1000000);

    for (int x = x1; x < size_process_child; x++) {
        TIMESTAMP *t = dynarrayTimestamps->timestamp + x;
        currentTime = t->admissao;
        mytime = localtime(&currentTime);
        ano = mytime->tm_year + 1900;


        sprintf(s,"C:\\Users\\tiago\\CLionProjects\\SO\\Data\\output-%d.txt",ano);
        fd = open(s, O_WRONLY | O_APPEND | O_CREAT, 0744);

        if (fd == -1) {
            perror("File open");
            exit(1);
        }

        sprintf(buf, "%d | %d | %d | %d | %d\n", t->admissao, t->ocupacaoET, t->ocupacaoT, t->ocupacaoSE,
                t->ocupacaoC);
        remove_timestamp_5_(dynarrayTimestamps,t->admissao);

        strcat(buf, "\n");
        write(fd, buf, strlen(buf));


        close(fd);
        free(buf);
    }



}
void remove_timestamp_5_(DYNARRAY_TIMESTAMPS *dynarrayTimestamps, int timestamp) {
    TIMESTAMP *t= dynarrayTimestamps->timestamp + dynarrayTimestamps->currentadmissao;
    TIMESTAMP tim = {0,0,0,0,0};
    TIMESTAMP *found_timestamp = find_timestamp_5_(dynarrayTimestamps, timestamp);


    while (found_timestamp < t) {
        *found_timestamp = *(found_timestamp + 1);
        found_timestamp++;
    }
    if (found_timestamp == t) {
        *found_timestamp = tim;
    }
    dynarrayTimestamps->currentadmissao--;

}

TIMESTAMP *find_timestamp_5_(DYNARRAY_TIMESTAMPS *dynarrayTimestamps, int timestamp) {
    TIMESTAMP *t = dynarrayTimestamps->timestamp;

    while (t != NULL) {
        if (timestamp == t->admissao) {
            return t;
        }
        t++;
    }

    return NULL;
}