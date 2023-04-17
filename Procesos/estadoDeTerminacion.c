#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t child;
    int estado;

    child = fork();
    if (child == 0) {
        printf("hijo: %d\n", getpid());
        return 15;
    }
    else {
        wait(&estado);
        if (WIFEXITED(estado))
        printf("Padre: hijo pid %d cod.t: %d\n", child, WEXITSTATUS(estado));
    }
    return 0;
}