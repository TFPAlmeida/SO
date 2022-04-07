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
    int currenttimestamp;
    TIMESTAMP * timestamp;
}DYNARRAY_TIMESTAMPS;

int main_process(int argc, char* argv[]);

void create_dynarray_timestamps(DYNARRAY_TIMESTAMPS * dynarrayTimestamps, int size);
void ler_ficheiro(DYNARRAY_TIMESTAMPS * dynarrayTimestamps);
void insert_dynarray_timestamps(DYNARRAY_TIMESTAMPS * dynarrayTimestamps, char admissao[], char inicio_triagem[], char fim_triagem[], char inicio_medico[], char fim_medico[]);
void print_Timestamps(DYNARRAY_TIMESTAMPS *dynarrayTimestamps);

#endif //SO_PROCESS_H

