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

typedef struct timestamp{
   int admissao;
   int inicio_triagem;
   int fim_triagem;
   int inicio_medico;
   int fim_medico;
}TIMESTAMP;

typedef struct lista_timestamps{
    int n_timestamps;
    int currentadmissao;
    TIMESTAMP * timestamp;
}DYNARRAY_TIMESTAMPS;

int main_process(int argc, char* argv[]);

void create_lista_timestamps(LISTA_TIMESTAMPS * listaTimestamps, int size);
void insert_timestamps(LISTA_TIMESTAMPS * listaTimestamps, int admissao, int inicio_triagem, int inicio_medico, int fim_medico);
void print_pais(LISTA_TIMESTAMPS *listaTimestamps);

#endif //SO_PROCESS_H

