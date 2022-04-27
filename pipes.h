//
// Created by tiago on 23/04/2022.
//

#ifndef SO_PIPES_H
#define SO_PIPES_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <math.h>


#define COLUMNS 5

typedef struct timestamp_1_{
    int admissao;
    int inicio_triagem;
    int fim_triagem;
    int inicio_medico;
    int fim_medico;
}TIMESTAMP_1_;

typedef struct lista_timestamps_1_{
    int n_timestamps;
    int currentadmissao;
    TIMESTAMP_1_ * timestamp;
}DYNARRAY_TIMESTAMPS_1_;

int main_pipes(int argc, char* argv[]);

int tamanho_do_ficheiro_1_( char nameficheiro[]);
void create_lista_timestamps_1_(DYNARRAY_TIMESTAMPS_1_ *dynarrayTimestamps, int size);
void ler_ficheiro_1_(DYNARRAY_TIMESTAMPS_1_ * dynarrayTimestamps, int lines );
void ocupacao_das_salas_1_(DYNARRAY_TIMESTAMPS_1_ * dynarrayTimestamps, int lines, int n, int fd[2]);
void print_timestamps_1_(DYNARRAY_TIMESTAMPS_1_ * dynarrayTimestamps, int lines);

#endif //SO_PIPES_H
