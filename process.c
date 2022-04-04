//
// Created by tiago on 31/03/2022.
//

#include "process.h"

#define MAX_STRING 10

int main_process(int argc, char *argv[]) {
    char line[MAX_STRING];
    int count = 0;
    char *delim = ";";


    DYNARRAY_TIMESTAMPS lt = {0, 0};
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

    //printf("%d", count);

    create_lista_timestamps(&lt,count);


    return 0;
}

void create_lista_timestamps(DYNARRAY_TIMESTAMPS * listaTimestamps, int size){
    listaTimestamps->timestamp = malloc(size * sizeof(TIMESTAMP));
    listaTimestamps->n_timestamps = size;
    listaTimestamps->currentadmissao = 0;

    FILE *file= fopen("C:\\Users\\tiago\\CLionProjects\\SO\\all_timestamps.csv", "r");
    char admissao[10],inicio_triagem[10],fim_triagem[10],inicio_medico[10],fim_medico[10];
    if (file == NULL) {
        printf("Nao foi possivel abrir o ficheiro\n");

    }else {

        while( file != EOF){
            fscanf(file,"%[^;]s %[^;]s %[^;]s %[^;]s %[^\n]s", admissao, inicio_triagem, fim_triagem, inicio_medico, fim_medico);
            TIMESTAMP *t = listaTimestamps->timestamp + listaTimestamps->currentadmissao;
            t->admissao = atoi(admissao);
            t->inicio_triagem = atoi(inicio_triagem);
            t->fim_triagem = atoi(fim_triagem);
            t->inicio_medico = atoi(inicio_medico);
            t->fim_medico = atoi(fim_medico);
            listaTimestamps->currentadmissao++;
        }
    }
    fclose(file);
    print_pais(&listaTimestamps);

}

void print_pais(DYNARRAY_TIMESTAMPS *listaTimestamps) {
    TIMESTAMP *t = listaTimestamps->timestamp;

    for (int i = 0; i < listaTimestamps->n_timestamps; i++) {
        printf("%d %d %d %d %d\n", t->admissao, t->inicio_triagem, t->fim_triagem, t->inicio_medico, t->fim_medico);
        t++;
    }
}





