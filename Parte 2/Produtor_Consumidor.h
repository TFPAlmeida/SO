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


typedef struct ocupacao {
    int timstamp_admicao;
    int ocupacao_ET;
    int ocupacao_T;
    int ocupacao_SE;
    int ocupacao_C;
    struct ocupacao * pnext;
    struct ocupacao * pprev;
} OCUPACAO;

typedef struct th_data{
    OCUPACAO * oc;
} TH_DATA;

#ifndef SO_PRODUTOR_CONSUMIDOR_H
#define SO_PRODUTOR_CONSUMIDOR_H

int main_PC(int argc, char* argv[]);
int tamanho_do_ficheiro_4_( char nameficheiro[]);
void ler_ficheiro_4_();
void ocupacao_das_salas_4_(int n);
void escrever_ficheiro_4_();
void print_timestamps_4_();
void *threads_produtor(void *parameters);
void *threads_consumidor(void *parameters);

#endif //SO_PRODUTOR_CONSUMIDOR_H
