//
// Created by tiago on 31/05/2022.
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

#ifndef SO_THREADS_H
#define SO_THREADS_H


int main_threads(int argc, char* argv[]);
int tamanho_do_ficheiro_3_( char nameficheiro[]);
void ler_ficheiro_3_();
void ocupacao_das_salas_3_(int n);
void escrever_ficheiro_3_(int timestamps, int ocupacao[4]);
void print_timestamps_3_();
void *threads_ocupacao(void *parameters);
#endif //SO_THREADS_H
