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
void create_dynarray_timestamps( int size);
void ler_ficheiro(int m_timestamps[][COLUMNS], int lines );
void insert_dynarray_timestamps(int m_timestamps[][COLUMNS], int lines , char admissao[], char inicio_triagem[], char fim_triagem[], char inicio_medico[], char fim_medico[]);
void ocupacao_das_salas(int m_timestamps[][COLUMNS], int lines, int n, char * path);
void ecrever_ficheiro(char * path, int timestamps, int sala_triagem , int triagem, int sala_de_espera, int consulta);
void read_INFO_txt(char * path);
void print_timestamps(int m_timestamps[][COLUMNS], int lines);

#endif //SO_PROCESS_H