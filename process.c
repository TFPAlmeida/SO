//
// Created by tiago on 31/03/2022.
//

#include "process.h"

#define PROCESS_NUM 2

int main_process(int argc, char *argv[]) {

    DYNARRAY_TIMESTAMPS dt = {0, 0};
    /******************************************************************************************************************/
    char nameficheiro[] = "C:\\Users\\tiago\\CLionProjects\\SO\\all_timestamps.csv";
    tamanho_do_ficheiro(&dt, nameficheiro);
    print_timestamps(&dt);
    /******************************************************************************************************************/
    int pids[PROCESS_NUM];
    dt.currenttimestamp = 0;
    for (int i = 0; i < PROCESS_NUM; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("Error in fork!");
        }

        if (pids[i] == 0) {
            //Child Process
            ocupacao_das_salas(&dt, 0);
            exit(0);
        }
    }
    //Main Process
    for (int i = 0; i < PROCESS_NUM; i++) {
        wait(NULL);
    }
    /******************************************************************************************************************/

    return 0;
}

void tamanho_do_ficheiro(DYNARRAY_TIMESTAMPS *dynarrayTimestamps, char nameficheiro[]) {
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
    create_dynarray_timestamps(dynarrayTimestamps, count);
    ler_ficheiro(dynarrayTimestamps);
}

void create_dynarray_timestamps(DYNARRAY_TIMESTAMPS *dynarrayTimestamps, int size) {
    dynarrayTimestamps->ptimestamp = malloc(size * sizeof(TIMESTAMP));
    dynarrayTimestamps->n_timestamps = size + 1;
    dynarrayTimestamps->currenttimestamp = 0;
    TIMESTAMP *t = dynarrayTimestamps->ptimestamp;
    for (int i = 0; i < dynarrayTimestamps->n_timestamps; i++) {
        t->admissao = 0;
        t->inicio_triagem = 0;
        t->fim_triagem = 0;
        t->fim_medico = 0;
        t->fim_medico = 0;
    }

}

void ler_ficheiro(DYNARRAY_TIMESTAMPS *dynarrayTimestamps) {
    FILE *file;
    file = fopen("C:\\Users\\tiago\\CLionProjects\\SO\\all_timestamps.csv", "r");

    char admissao[11], inicio_triagem[11], fim_triagem[11], inicio_medico[11], fim_medico[11], line[100];
    char *delim = ";";
    char *delim2 = "\n";

    if (file == NULL) {
        printf("Nao foi possivel abrir o ficheiro\n");

    }

    while (fgets(line, sizeof(line), (FILE *) file) != NULL) {

        strcpy(admissao, strtok(line, delim));
        strcpy(inicio_triagem, strtok(NULL, delim));
        strcpy(fim_triagem, strtok(NULL, delim));
        strcpy(inicio_medico, strtok(NULL, delim));
        strcpy(fim_medico, strtok(NULL, delim2));
        insert_dynarray_timestamps(dynarrayTimestamps, admissao, inicio_triagem, fim_triagem, inicio_medico,
                                   fim_medico);

    }

    fclose(file);

}

void insert_dynarray_timestamps(DYNARRAY_TIMESTAMPS *dynarrayTimestamps, char admissao[], char inicio_triagem[],
                                char fim_triagem[], char inicio_medico[], char fim_medico[]) {
    TIMESTAMP *t = dynarrayTimestamps->ptimestamp + dynarrayTimestamps->currenttimestamp;
    t->admissao = atoi(admissao);
    t->inicio_triagem = atoi(inicio_triagem);
    t->fim_triagem = atoi(fim_triagem);
    t->inicio_medico = atoi(inicio_medico);
    t->fim_medico = atoi(fim_medico);
    printf("%d %d %d %d %d\n", t->admissao, t->inicio_triagem, t->fim_triagem, t->inicio_medico, t->fim_medico);
    dynarrayTimestamps->currenttimestamp++;
}

/*
void print_timestamps(DYNARRAY_TIMESTAMPS * dynarrayTimestamps){
    TIMESTAMP *t = dynarrayTimestamps->ptimestamp;
    for(int i = 0; i < dynarrayTimestamps->n_timestamps; i++){
        printf("%d %d %d %d %d\n", t->admissao, t->inicio_triagem, t->fim_triagem, t->inicio_medico, t->fim_medico);
        t++;
    }
}
*/

void ocupacao_das_salas(DYNARRAY_TIMESTAMPS * dynarrayTimestamps, int timestamp) {
    int size = dynarrayTimestamps->n_timestamps;
    TIMESTAMP *t = dynarrayTimestamps->ptimestamp + dynarrayTimestamps->currenttimestamp;
    int sala_triagem = 0, triagem = 0, sala_de_espera = 0, consulta = 0;
    int size_process_child = size / PROCESS_NUM;
    for(int i = 0; i < size_process_child; i++){
        if(t->admissao > timestamp && t->inicio_triagem < timestamp){
            sala_triagem++;
        }else if(t->inicio_triagem > timestamp && t->fim_triagem < timestamp){
            triagem++;
        }else if(t->fim_triagem > timestamp && t->inicio_medico < timestamp){
            sala_de_espera++;
        }else if(t->inicio_medico > timestamp && t->fim_medico < timestamp){
            consulta++;
        }
        dynarrayTimestamps->currenttimestamp++;
    }

}






