//
// Created by tiago on 31/03/2022.
//

#include "process.h"

#define PROCESS_NUM 2

char path[100] = "C:\\Users\\tiago\\CLionProjects\\SO\\INFO_TXT.txt";

int main_process(int argc, char *argv[]) {


    /******************************************************************************************************************/
    char nameficheiro[] = "C:\\Users\\tiago\\CLionProjects\\SO\\all_timestamps.csv";
    char file_INFO_TXT[] = "../data/ficheirostxt/INFO_TXT.txt";
    int t_ficheiro = tamanho_do_ficheiro(nameficheiro);
    int m_timestamps[t_ficheiro][COLUMNS];
    int lines = t_ficheiro;
    ler_ficheiro(m_timestamps, lines);
    print_timestamps(m_timestamps, lines);
    /******************************************************************************************************************/
    /*int pids[PROCESS_NUM];

    for (int i = 1; i <= PROCESS_NUM; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("Error in fork!");
        }

        if (pids[i] == 0) {
            //Child Process
            ocupacao_das_salas(m_timestamps, lines, i, path);
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


void print_timestamps(int m_timestamps[][COLUMNS], int lines) {

    for (int i = 0; i < lines; i++) {
        for (int x = 0; x < COLUMNS; x++) {
            printf("%d ", *(*(m_timestamps + i) + x));
        }
        printf("\n");
    }
}


void ocupacao_das_salas(int m_timestamps[][COLUMNS], int lines, int n, char *path) {
    int sala_triagem = 0, triagem = 0, sala_de_espera = 0, consulta = 0;
    int size = lines / PROCESS_NUM;
    int size_process_child = size * n;
    int x1 = 0, timestamps;
    if (n == PROCESS_NUM && lines % 2 != 0) {
        size_process_child++;
    }

    if (n != 1) {
        x1 = size * (n - 1);
    }

    for (int x = x1; x < size_process_child; x++) {
        for (int y = 0; y < COLUMNS; y++) {
            timestamps = *(*(m_timestamps + x) + y);
            for (int z = x1; z < size_process_child; z++) {
                if (*(*(m_timestamps + z) + 0) < timestamps < *(*(m_timestamps + z) + 1)) {
                    sala_triagem++;
                }
                if (*(*(m_timestamps + z) + 1) < timestamps < *(*(m_timestamps + z) + 2)) {
                    triagem++;
                }
                if (*(*(m_timestamps + z) + 2) < timestamps < *(*(m_timestamps + z) + 3)) {
                    sala_de_espera++;
                }
                if (*(*(m_timestamps + z) + 3) < timestamps < *(*(m_timestamps + z) + 4)) {
                    consulta++;
                }
            }
            ecrever_ficheiro(path, timestamps, sala_triagem, triagem, sala_de_espera, consulta);
            sala_triagem = 0;
            triagem = 0;
            sala_de_espera = 0;
            consulta = 0;
        }
    }

}

void ecrever_ficheiro(char *path, int timestamps, int sala_triagem, int triagem, int sala_de_espera, int consulta) {
    int fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0744);

    if (fd == -1) {
        perror("File open");
        exit(1);
    }

    char *buf = (char *) malloc(sizeof(char) * 1000000);

    sprintf(buf, "id: %d | timestamp: %d | sala: sala de triagem | ocupacao: %d\n", getpid(), timestamps, sala_triagem);
    sprintf(buf, "id: %d | timestamp: %d | sala: triagem | ocupacao: %d\n", getpid(), timestamps, triagem);
    sprintf(buf, "id: %d | timestamp: %d | sala: sala de espera | ocupacao: %d\n", getpid(), timestamps,
            sala_de_espera);
    sprintf(buf, "id: %d | timestamp: %d | sala: sala de triagem | ocupacao: %d\n", getpid(), timestamps, consulta);

    strcat(buf, "\n");
    write(fd, buf, strlen(buf));


    close(fd);
    free(buf);
    read_INFO_txt(path);
}

void read_INFO_txt(char * path) {
    long bytes, total=0, size;

    char * cds=NULL;

    int fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        perror("File open");
        exit(1);
    }

    size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    cds = (char *) malloc(sizeof(char) * (size+1));
    while ((bytes = read(fd, cds+total, 4096)))
        total += bytes;

    close(fd);

}




