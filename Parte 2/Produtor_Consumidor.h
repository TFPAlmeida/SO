//
// Created by tiago on 03/06/2022.
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

#ifndef SO_PRODUTOR_CONSUMIDOR_H
#define SO_PRODUTOR_CONSUMIDOR_H

typedef struct timestamp{
    int admissao;
    int ocupacaoET;
    int ocupacaoT;
    int ocupacaoSE;
    int ocupacaoC;
}TIMESTAMP;

typedef struct lista_timestamps{
    int currentadmissao;
    TIMESTAMP * timestamp;
}DYNARRAY_TIMESTAMPS;

int main_PC(int argc, char* argv[]);
int tamanho_do_ficheiro_4_( char nameficheiro[]);
void ler_ficheiro_4_();
void ocupacao_das_salas_4_(DYNARRAY_TIMESTAMPS *dynarrayTimestamps, int n);
void escrever_ficheiro_4_(DYNARRAY_TIMESTAMPS *dynarrayTimestamps);
void print_timestamps_4_();
void *Produtor(void *parameters);
void *Consumidor(void *parameters);
TIMESTAMP *find_timestamp(DYNARRAY_TIMESTAMPS *dynarrayTimestamps, int timestamp);
void remove_timestamp(DYNARRAY_TIMESTAMPS *dynarrayTimestamps, int timestamp);
#endif //SO_PRODUTOR_CONSUMIDOR_H
