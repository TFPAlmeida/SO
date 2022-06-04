//
// Created by tiago on 31/03/2022.
//

#include "pipes.h"

#define SIZE 10000
#define PROCESS_NUM 2


char *salas_1_[] = {"sala_triagem", "triagem", "sala_de_espera", "consulta"};

int main_pipes(int argc, char *argv[]) {


    /******************************************************************************************************************/
    char nameficheiro[] = "C:\\Users\\tiago\\CLionProjects\\SO\\Data\\all_timestamps.csv";

    int t_ficheiro = tamanho_do_ficheiro_1_(nameficheiro);
    int lines = t_ficheiro;
    int** arr = (int**)malloc(lines * sizeof(int*));
    for (int index=0;index<lines;++index)
    {
        arr[index] = (int*)malloc(5 * sizeof(int));
    }

    ler_ficheiro_1_(arr, lines);
    print_timestamps_1_(arr, lines);
    char buffer[SIZE];
    /******************************************************************************************************************/
    /*int pids[PROCESS_NUM];
    int fd[2];

    for (int i = 0; i < PROCESS_NUM; i++) {
        if (pipe(fd) == -1) {
            perror("Error with creating pipe\n");
        }
    }
    for (int i = 1; i <= PROCESS_NUM; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("Error with creating process\n");
        }
        if (pids[i] == 0) {
            //Child Process
            close(fd[0]);
            ocupacao_das_salas_1_(arr, lines, i, fd);
            close(fd[1]);
            exit(0);
        }
    }
    //Main Process

    int ocupacao_2_[4], id_2_, timestamps_2_;
    char *salas_2_[4];
    int ficheiro = open("C:\\Users\\tiago\\CLionProjects\\SO\\Data\\pipe.txt", O_WRONLY|O_APPEND|O_CREAT, 0666);
    close(fd[1]);
    dup(ficheiro);
    ssize_t n;
    while ((n = readn(fd[0], buffer, SIZE)) > 0)   // pai vai ler do pipe
    {
        write(ficheiro, buffer, sizeof(buffer));
    }


    wait(NULL);
    close(fd[0]);
*/
    /******************************************************************************************************************/
    return 0;
}

int tamanho_do_ficheiro_1_(char nameficheiro[]) {
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

    return count;
}


void ler_ficheiro_1_(int** arr, int lines) {
    FILE *file;
    file = fopen("C:\\Users\\tiago\\CLionProjects\\SO\\Data\\all_timestamps.csv", "r");

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

        *(*(arr + i) + 0) = atoi(admissao);
        *(*(arr + i) + 1) = atoi(inicio_triagem);
        *(*(arr + i) + 2) = atoi(fim_triagem);
        *(*(arr + i) + 3) = atoi(inicio_medico);
        *(*(arr + i) + 4) = atoi(fim_medico);
        i++;
    }
}

void ocupacao_das_salas_1_(int** arr, int lines, int n, int fd[2]) {

    int size = lines / PROCESS_NUM;
    int size_process_child = size * n;
    int x1 = 0, timestamps, id = getpid();;
    int ocupacao[4] = {0, 0, 0, 0};
    if (n == PROCESS_NUM && lines % 2 != 0) {
        size_process_child++;
    }

    if (n != 1) {
        x1 = size * (n - 1);
    }


    for (int x = x1; x < size_process_child; x++) {
        for (int z = 0; z < COLUMNS; z++) {
            timestamps = *(*(arr + x) + z);
            for (int y = x1; y < size_process_child; y++) {

                if (*(*(arr + y) + 0) < timestamps < *(*(arr + y) + 1)) {
                    ocupacao[0]++;
                }
                if (*(*(arr + y) + 1) < timestamps < *(*(arr + y) + 2)) {
                    ocupacao[1]++;
                }
                if (*(*(arr + y) + 3) < timestamps < *(*(arr + y) + 4)) {
                    ocupacao[2]++;
                }
                if (*(*(arr + y) + 4) < timestamps < *(*(arr + y) + 5)) {
                    ocupacao[3]++;
                }
            }

            char *buf = (char *) malloc(sizeof(char) * 1000000);
            for (int i = 0; i < 4; i++) {
                sprintf(buf, "id: %d | timestamp: %d | sala: %s | ocupacao: %d", id, timestamps, *(salas_1_ + i), ocupacao[i]);
                strcat(buf, "\n");
                writen(fd[1], buf, strlen(buf));
                ocupacao[i] = 0;
            }
            free(buf);
        }


    }


}

void print_timestamps_1_(int** arr, int lines) {

    for(int x = 0; x < lines; x++){
        for(int y = 0; y < COLUMNS; y++){
            printf("%d ", *(*(arr + x) + y));
        }
        printf("\n");
    }

}

ssize_t                          //Read "n" bytes from a descriptor.
readn(int fd, void *vptr, size_t n)
{
    size_t  nleft;
    ssize_t nread;
    char   *ptr;

    ptr = vptr;
    nleft = n;
    while (nleft > 0)
    {
        if ( (nread = read(fd, ptr, nleft)) < 0)
        {
            if (errno == EINTR)
                nread = 0;
                //and call read() again
            else
                return (-1);
        }
        else if (nread == 0)
            break;
        //EOF

        nleft -= nread;
        ptr += nread;
    }
    return (n - nleft);
    //return >= 0
}

ssize_t                         // Write "n" bytes to a descriptor.
writen(int fd, const void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;

    ptr = vptr;
    nleft = n;
    while (nleft > 0)
    {
        if ( (nwritten = write(fd, ptr, nleft)) <= 0)
        {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0;
                //and call write() again
            else
                return (-1);
            //error
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return (n);
}

