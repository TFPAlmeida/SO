//
// Created by tiago on 24/04/2022.
//

#ifndef SO_PIPES_2__H
#define SO_PIPES_2__H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>


#define COLUMNS 5

int main_pipes_2_(int argc, char* argv[]);
int tamanho_do_ficheiro_2_(char nameficheiro[]);
void ler_ficheiro_2_(int** arr, int lines);
void ocupacao_das_salas_2_(int** arr, int lines, int n, int fds[][2], int PROCESS_NUM);
void print_timestamps_2_(int** arr, int lines);
ssize_t readn(int fd, void *vptr, size_t n);
ssize_t writen(int fd, const void *vptr, size_t n);
#endif //SO_PIPES_2__H
