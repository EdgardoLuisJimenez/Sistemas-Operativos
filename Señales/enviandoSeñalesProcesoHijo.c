#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

void *oldhandler;
void sighandler(int sig) { printf("sig %d capturada\n", sig); }

int main() {
  pid_t pidhijo;
  oldhandler = signal(SIGUSR1, sighandler);
  if (oldhandler == SIG_ERR) {
    perror("signal:");
    exit(EXIT_FAILURE);
  }

  pidhijo = fork();

  switch (pidhijo) {
  case -1:
    perror("fork");
    break;
  case 0:
    pause();
    printf("[%d]Terminando\n", getpid());
    break;
  default:
    usleep(100);
    kill(pidhijo, SIGUSR1);
    printf("[%d]Señal enviada\n", getpid());
    wait(NULL);
    break;
  }

  if (signal(SIGUSR1, oldhandler) == SIG_ERR) {
    perror("signal:");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}