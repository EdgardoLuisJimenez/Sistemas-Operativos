#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

#define MAX_CHARS 5 // incluye el caracter nulo

void *oldhandler;
char message[MAX_CHARS] = {72, 101, 108, 108, 111}; // mensaje "hello" en código ASCII
int signal_h = 3;                                   // cantidad de señales SIGUSR1 a enviar
int signal_o = 5;                                   // cantidad de señales SIGUSR2 a enviar
int signal_l = 2;                                   // cantidad de señales SIGUSR1 a enviar
int signal_a = 1;                                   // cantidad de señales SIGUSR2 a enviar

void sighandler(int sig)
{
    int i;
    printf("[%d]Recibido mensaje: ", getpid());
    for (i = 0; i < MAX_CHARS; i++)
    {
        printf("%c", message[i]);
    }
    printf("\n");
    exit(EXIT_SUCCESS);
}

int main()
{
    pid_t pidhijo;
    oldhandler = signal(SIGUSR1, sighandler);
    if (oldhandler == SIG_ERR)
    {
        perror("signal:");
        exit(EXIT_FAILURE);
    }

    pidhijo = fork();
    switch (pidhijo)
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
    case 0:
        pause();
        break;
    default:
        int i, j;
        for (i = 0; i < signal_h; i++)
        {
            for (j = 0; j < MAX_CHARS; j++)
            {
                if (message[j] == 'h')
                {
                    kill(pidhijo, SIGUSR1);
                }
            }
            usleep(100);
        }
        for (i = 0; i < signal_o; i++)
        {
            for (j = 0; j < MAX_CHARS; j++)
            {
                if (message[j] == 'o')
                {
                    kill(pidhijo, SIGUSR2);
                }
            }
            usleep(100);
        }
        for (i = 0; i < signal_l; i++)
        {
            for (j = 0; j < MAX_CHARS; j++)
            {
                if (message[j] == 'l')
                {
                    kill(pidhijo, SIGUSR1);
                }
            }
            usleep(100);
        }
        for (i = 0; i < signal_a; i++)
        {
            for (j = 0; j < MAX_CHARS; j++)
            {
                if (message[j] == 'a')
                {
                    kill(pidhijo, SIGUSR2);
                }
            }
            usleep(100);
        }
        printf("[%d]Enviando mensaje: ", getpid());
        for (j = 0; j < MAX_CHARS; j++)
        {
            printf("%c", message[j]);
        }
        printf("\n");
        wait(NULL);
    }

    if (signal(SIGUSR1, oldhandler) == SIG_ERR)
    {
        perror("signal:");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
