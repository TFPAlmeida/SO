//
// Created by tiago on 31/03/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <math.h>

#ifndef SO_PROCESS_H
#define SO_PROCESS_H
#define COLUMNS 5

typedef struct timestamp{
    int admissao;
    int inicio_triagem;
    int fim_triagem;
    int inicio_medico;
    int fim_medico;
}TIMESTAMP;

typedef struct lista_timestamps{
    int n_timestamps;
    int currentadmissao;
    TIMESTAMP * timestamp;
}DYNARRAY_TIMESTAMPS;

int main_process(int argc, char* argv[]);
int tamanho_do_ficheiro( char nameficheiro[]);
void create_lista_timestamps(DYNARRAY_TIMESTAMPS * dynarrayTimestamps, int size);
void ler_ficheiro(DYNARRAY_TIMESTAMPS * dynarrayTimestamps, int lines );
void ocupacao_das_salas(DYNARRAY_TIMESTAMPS * dynarrayTimestamps, int lines, int n);
void escrever_ficheiro(char * path,int timestamps, int ocupacao[4]);
void read_INFO_txt(char * path);
void print_timestamps(DYNARRAY_TIMESTAMPS * dynarrayTimestamps, int lines);

#endif //SO_PROCESS_H