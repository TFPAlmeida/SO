//
// Created by tiago on 31/03/2022.
//

#include "process.h"

int main_process(int argc, char *argv[]) {
    int count = 0;

    DYNARRAY_TIMESTAMPS dt = {0, 0};
    FILE *fp;
    fp = fopen("C:\\Users\\tiago\\CLionProjects\\SO\\all_timestamps.csv", "r");

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

    create_dynarray_timestamps(&dt, count);
    ler_ficheiro(&dt);

    return 0;
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

    while ( fgets(line, sizeof(line), (FILE *) file) != NULL) {

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






