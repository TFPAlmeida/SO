//
// Created by tiago on 31/03/2022.
//

#include "process.h"

#define PROCESS_NUM 2


int main_process(int argc, char *argv[]) {


    /******************************************************************************************************************/
    char nameficheiro[] = "C:\\Users\\tiago\\CLionProjects\\SO\\all_timestamps.csv";
    int t_ficheiro = tamanho_do_ficheiro( nameficheiro);
    int m_timestamps [t_ficheiro][COLUMNS];
    int lines = t_ficheiro;
    ler_ficheiro(m_timestamps, lines);
    print_timestamps(m_timestamps, lines);
    /******************************************************************************************************************/
    /*int pids[PROCESS_NUM];
    dt.currenttimestamp = 0;
    for (int i = 0; i < PROCESS_NUM; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("Error in fork!");
        }

        if (pids[i] == 0) {
            //Child Process
            ocupacao_das_salas(&dt, 0);
            exit(0);
        }
    }
    //Main Process
    for (int i = 0; i < PROCESS_NUM; i++) {
        wait(NULL);
    }*/
    /******************************************************************************************************************/

    return 0;
}

int tamanho_do_ficheiro(char nameficheiro[]) {
    int count = 0;
    FILE *fp;
    fp = fopen(nameficheiro, "r");

    if (fp == NULL) {
        perror("Nao foi possivel ler o ficheiro!\n");
    }

    char c;

    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            count++;
        }
    }
    fclose(fp);

    return count + 1;
}

void ler_ficheiro(int (*m_timestamps)[COLUMNS], int lines) {
    FILE *file;
    file = fopen("C:\\Users\\tiago\\CLionProjects\\SO\\all_timestamps.csv", "r");

    char admissao[11], inicio_triagem[11], fim_triagem[11], inicio_medico[11], fim_medico[11], line[100];
    char *delim = ";";
    char *delim2 = "\n";

    if (file == NULL) {
        printf("Nao foi possivel abrir o ficheiro\n");

    }

    int i = 0;

    while (fgets(line, sizeof(line), (FILE *) file) != NULL) {

        strcpy(admissao, strtok(line, delim));
        strcpy(inicio_triagem, strtok(NULL, delim));
        strcpy(fim_triagem, strtok(NULL, delim));
        strcpy(inicio_medico, strtok(NULL, delim));
        strcpy(fim_medico, strtok(NULL, delim2));

        *(*(m_timestamps + i) + 0) = atoi(admissao);
        *(*(m_timestamps + i) + 1) = atoi(inicio_triagem);
        *(*(m_timestamps + i) + 2) = atoi(fim_triagem);
        *(*(m_timestamps + i) + 3) = atoi(inicio_medico);
        *(*(m_timestamps + i) + 4) = atoi(fim_medico);

        i++;
    }




}


void print_timestamps(int m_timestamps[][COLUMNS], int lines){

    for(int i = 0; i < lines; i++){
        for(int x = 0; x < COLUMNS; x++){
            printf("%d ", *(*(m_timestamps + i) + x));
        }
        printf("\n");
    }
}

/*
void ocupacao_das_salas(DYNARRAY_TIMESTAMPS * dynarrayTimestamps, int timestamp) {
    int size = dynarrayTimestamps->n_timestamps;
    TIMESTAMP *t = dynarrayTimestamps->ptimestamp + dynarrayTimestamps->currenttimestamp;
    int sala_triagem = 0, triagem = 0, sala_de_espera = 0, consulta = 0;
    int size_process_child = size / PROCESS_NUM;
    for(int i = 0; i < size_process_child; i++){
        if(t->admissao > timestamp && t->inicio_triagem < timestamp){
            sala_triagem++;
        }else if(t->inicio_triagem > timestamp && t->fim_triagem < timestamp){
            triagem++;
        }else if(t->fim_triagem > timestamp && t->inicio_medico < timestamp){
            sala_de_espera++;
        }else if(t->inicio_medico > timestamp && t->fim_medico < timestamp){
            consulta++;
        }
        dynarrayTimestamps->currenttimestamp++;
    }

}*/






