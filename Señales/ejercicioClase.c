#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void *handler;

void funcHandler(int sig)
{
  printf("%d\n", getpid());
}
int main(int argc, char **argv)
{
  handler = signal(SIGUSR1, funcHandler);
  pid_t parent = getpid();
  pid_t *childs = malloc(4 * sizeof(pid_t));
  pid_t childchild;
  int i;
  for (i = 0; i != 3; ++i)
  {
    childs[i] = fork();
    if (childs[i] == 0)
    {
      if (i == 1)
        childchild = fork();
      break;
    }
  }

  if (parent == getpid())
  {

    usleep(5000);
    char cmd[50];
    sprintf(cmd, "pstree -p -l %d", getpid());
    system(cmd);
    usleep(5000);

    for (int j = 0; j < atoi(argv[1]); ++j)
    {
      printf("=============================================================\n");
      printf("Padre-Hijo 3:\n");
      usleep(200);
      kill(childs[2], SIGUSR1);
      pause();
    }
    for (int k = 0; k < 3; ++k)
      wait(NULL);
  }
  else
  {
    for (int j = 0; j < atoi(argv[1]); ++j)
    {
      pause();

      switch (i)
      {
      case 2:
        printf("HIjo 3 - Hijo 2\n");
        kill(childs[1], SIGUSR1);
        break;
      case 1:
        if (childchild != 0)
        {
          printf("Hijo 2 - Hijo 2.5\n");
          kill(childchild, SIGUSR1);
          usleep(100);
          printf("Hijo 2 - Hijo 1\n");
          kill(childs[0], SIGUSR1);
        }
        else
        {
          printf("Hijo 2.5 - Hijo 2\n");
          kill(getppid(), SIGUSR1);
        }
        break;
      case 0:
        printf("Hijo 1 - Padre\n");
        kill(parent, SIGUSR1);
        break;
      default:
        break;
      }
    }
  }

  free(childs);
}