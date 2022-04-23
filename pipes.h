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

int tamanho_do_ficheiro( char nameficheiro[]);
void ler_ficheiro(int m_timestamps[][COLUMNS], int lines );
int * ocupacao_das_salas(int m_timestamps[][COLUMNS], int lines, int n, char * path, int fd[2]);
void ecrever_ficheiro(char * path,int timestamps, int ocupacao[4], char * salas[4]);
void read_INFO_txt(char * path);
void print_timestamps(int m_timestamps[][COLUMNS], int lines);

#endif //SO_PIPES_H
