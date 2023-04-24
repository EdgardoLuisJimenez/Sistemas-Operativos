#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

void *oldhandler;
void sighandler(int sig)
{
  // printf("[%d]sig %d capturada\n", getpid(), sig);
}

#define N_HIJOS 3

int main()
{
  pid_t root, grandchild;
  int i = 0;
  // Asignando memoria dinamica a un array
  int *array = (int *)malloc(N_HIJOS * sizeof(int));
  // Verificando la asignacion correcta del array
  if (array == NULL)
  {
    printf("No se pudo asignar memoria\n");
    exit(EXIT_FAILURE);
  }

  oldhandler = signal(SIGUSR1, sighandler);
  if (oldhandler == SIG_ERR)
  {
    perror("signal:");
    exit(EXIT_FAILURE);
  }

  root = getpid();
  for (i = 0; i < 3; i++)
  {
    array[i] = fork();
    if (array[i] == 0)
    {
      if (i == 1)
      {
        if ((grandchild = fork()) == 0)
        {
          break;
        }
      }
      break;
    }
  }

  if (root == getpid())
  {
    usleep(10000);
    printf("Padre [%d]\n", getpid());
    kill(array[2], SIGUSR1);
    pause();
    printf("Padre [%d]\n", getpid());

    for (int j = 0; j < N_HIJOS; j++)
    {
      wait(NULL);
    }
  }
  else
  {
    pause();
    if (i == 2)
    {
      printf("hijo[%d]\n", getpid());
      kill(array[i - 1], SIGUSR1);
    }
    else if (i == 1)
    {
      if (grandchild != 0)
      {
        printf("hijo[%d]\n", getpid());
        kill(grandchild, SIGUSR1);
        pause();
        printf("hijo[%d]\n", getpid());
        usleep(1000);
        kill(array[i - 1], SIGUSR1);
      }
      else
      {
        pause();
        printf("hijo[%d] - padre[%d]\n", getpid(), getppid());
        kill(getppid(), SIGUSR1);
      }
    }
    else if (i == 0)
    {
      printf("hijo[%d]\n", getpid());
      kill(getppid(), SIGUSR1);
    }
  }

  signal(SIGUSR1, oldhandler);
  return EXIT_SUCCESS;
}