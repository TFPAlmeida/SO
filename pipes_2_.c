//
// Created by tiago on 24/04/2022.
//

#include "pipes_2_.h"

struct tm *mytime;
/*
void handler(int signal_number)
{
    if(signal_number == SIGUSR1)
    {

    }
}

int main_pipes_2_(int argc, char *argv[]) {
    time_t currentTime;
    char nameficheiro[] = "C:\\Users\\tiago\\CLionProjects\\SO\\all_timestamps.csv";
    int t_ficheiro = tamanho_do_ficheiro_2_(nameficheiro);
    int m_timestamps[t_ficheiro][COLUMNS];
    int lines = t_ficheiro;
    ler_ficheiro_2_(m_timestamps, lines);

    int arr[t_ficheiro * 5];
    int z = 0;
    for (int x = 0; x < t_ficheiro; x++) {
        for (int y = 0; y < COLUMNS; y++) {
            currentTime = *(*(m_timestamps + x) + y);
            mytime = localtime(&currentTime);
            arr[z] = mytime->tm_year + 1900;
            z++;
        }
    }
    int count = 0;
    for(int i = 0;  i < t_ficheiro * 5; i++){
        if(arr[0] != arr[i]){
            count++;
        }
    }

    int pids[count], fds[count][2];

    for (int i = 1; i <= count; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("Error with creating process\n");
        }
        if (pids[i] == 0) {
            //Child Process

            exit(0);
        }
    }
    //Main Process
    for (int i = 0; i < count; i++) {
        wait(NULL);
    }



    return 0;
}

int tamanho_do_ficheiro_2_(char nameficheiro[]) {
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

void ler_ficheiro_2_(int (*m_timestamps)[COLUMNS], int lines) {
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
}*/