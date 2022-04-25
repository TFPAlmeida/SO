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


int main_pipes(int argc, char* argv[]);

int tamanho_do_ficheiro_1_( char nameficheiro[]);
void ler_ficheiro_1_(int m_timestamps[][COLUMNS], int lines );
void ocupacao_das_salas_1_(int m_timestamps[][COLUMNS], int lines, int n, int fd[2]);
void print_timestamps_1_(int m_timestamps[][COLUMNS], int lines);

#endif //SO_PIPES_H
