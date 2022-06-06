//
// Created by tiago on 05/06/2022.
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

#ifndef SO_PRODUTOR_CONSUMIDOR_2__H
#define SO_PRODUTOR_CONSUMIDOR_2__H

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

int main_PC2(int argc, char* argv[]);
int tamanho_do_ficheiro_5_( char nameficheiro[]);
void ler_ficheiro_5_();
void ocupacao_das_salas_5_(DYNARRAY_TIMESTAMPS *dynarrayTimestamps, int n);
void escrever_ficheiro_5_(DYNARRAY_TIMESTAMPS *dynarrayTimestamps);
void print_timestamps_5_();
void *Produtor2(void *parameters);
void *Consumidor2(void *parameters);
TIMESTAMP *find_timestamp_5_(DYNARRAY_TIMESTAMPS *dynarrayTimestamps, int timestamp);
void remove_timestamp_5_(DYNARRAY_TIMESTAMPS *dynarrayTimestamps, int timestamp);

#endif //SO_PRODUTOR_CONSUMIDOR_2__H
