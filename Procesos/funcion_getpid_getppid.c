#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// pid_t getpid(void);
// pid_t getppid(void);// getppid = get parent pid

int main(void) {
    pid_t pidchild = fork();
    switch (pidchild) {
        case -1:
            perror("Error fork");
            exit(EXIT_FAILURE);
            break;
        case 0:
            printf("Proceso hijo: pid=%d y ppid=%d\n", getpid(), getppid());
            break;
        default:
            printf("Proceso padre: pid=%d y ppid=%d\n", getpid(), getppid());
    }
    return EXIT_SUCCESS;
}