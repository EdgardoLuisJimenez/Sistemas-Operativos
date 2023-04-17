#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void *oldhandler;
void sighandler(int sig)
{

  /*

  */
}

int main()
{
  oldhandler = signal(SIGUSR1, sighandler);

  if (oldhandler == SIG_ERR)
  {
    perror("Signal:");
    exit(EXIT_FAILURE);
  }

  /*





  */
  if (signal(SIGUSR1, oldhandler) == SIG_ERR)
  {
    perror("Signal:");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}