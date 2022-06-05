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

int main_PC2(int argc, char* argv[]);
int tamanho_do_ficheiro_5_( char nameficheiro[]);
void ler_ficheiro_5_();
void ocupacao_das_salas_5_(int n);
void escrever_ficheiro_5_();
void print_timestamps_5_();
void *threads_produtor2(void *parameters);
void *threads_consumidor2(void *parameters);

#endif //SO_PRODUTOR_CONSUMIDOR_2__H
