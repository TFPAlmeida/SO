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


int main_process(int argc, char* argv[]);
int tamanho_do_ficheiro( char nameficheiro[]);

void ler_ficheiro(int** arr, int lines );
void ocupacao_das_salas(int** arr, int lines, int n);
void escrever_ficheiro(char * path,int timestamps, int ocupacao[4]);
void read_INFO_txt(char * path);
void print_timestamps(int** arr, int lines);

#endif //SO_PROCESS_H