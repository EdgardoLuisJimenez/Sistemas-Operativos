#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

void *oldhandler;
void sighandler(int sig)
{ // Sincroniza procesos padre e hijo
  // printf("[%d]sig %d capturada\n", getpid(), sig);
}

#define n_hijos 3 // Es una macro

int main()
{
    pid_t pidhijo[n_hijos];
    pid_t pidhijo2;
    pid_t pidhijo3;
    int i, j, n, k;

    printf("N:?");
    scanf("%d", &n);

    oldhandler = signal(SIGUSR1, sighandler);
    if (oldhandler == SIG_ERR)
    {
        perror("signal:");
        exit(EXIT_FAILURE);
    }

    int root = getpid();
    for (i = 0; i < n_hijos; i++)
    {
        pidhijo[i] = fork();
        if (pidhijo[i] == 0)
        {
            if (i == 0)
            {
                if ((pidhijo3 = fork()) == 0)
                {
                    break;
                }
            }
            else if (i == 2)
            {
                if ((pidhijo2 = fork()) == 0)
                {
                    break;
                }
            }
            break;
        }
    }

    if (root == getpid())
    {

        for (k = 0; k < n; k++)
        {
            usleep(10000);
            printf("Padre [%d]\n", getpid());
            kill(pidhijo[n_hijos - 1], SIGUSR1);
            pause();
            printf("Padre [%d]\n", getpid());
        }
        for (j = 0; j < n_hijos; j++)
            wait(NULL);
    }
    else
    {
        for (k = 0; k < n; k++)
        {
            pause();
            switch (i)
            {
            case 2: // Ojo como estan en el mismo nivel de jerarquia ingresa el hijo y el padre de ese hijo
                if (pidhijo2 != 0)
                {
                    printf("hijo[%d]\n", getpid());
                    kill(pidhijo2, SIGUSR1);
                    // pause();
                    usleep(1000);
                    kill(pidhijo[i - 1], SIGUSR1);
                }
                else
                {
                    // pause();
                    printf("hijo[%d]\n", getpid());
                    kill(getppid(), SIGUSR1);
                }
                break;
            case 1:
                printf("hijo[%d]\n", getpid());
                kill(pidhijo[i - 1], SIGUSR1);
                break;
            case 0: ////Ojo como estan en el mismo nivel de jerarquia ingresa el hijo y el padre de ese hijo
                if (pidhijo3 != 0)
                {
                    printf("hijo[%d]\n", getpid());
                    kill(pidhijo3, SIGUSR1);
                    // pause();
                    usleep(1000);
                    printf("hijo[%d]\n", getpid());
                    kill(getppid(), SIGUSR1);
                }
                else
                {
                    // pause();
                    printf("hijo[%d]\n", getpid());
                    kill(getppid(), SIGUSR1);
                }
                break;
            default:
                break;
            }
        }
    }
}