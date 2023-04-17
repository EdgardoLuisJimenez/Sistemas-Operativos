#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int count = 0;
void *oldhandler;
void sighandler(int sig) { count++; }

int main() {
  oldhandler == signal(SIGINT, sighandler);
  if (oldhandler == SIG_ERR) {
    perror("Signal:");
    exit(EXIT_FAILURE);
  }

  do {

  } while (count < 3);
  printf("\n %d veces SIGINT recibida\n", count);

  if (signal(SIGUSR1, oldhandler) == SIG_ERR) {
    perror("Signal:");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}