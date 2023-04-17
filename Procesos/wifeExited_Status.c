#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main (void) {
    int estado;
    pid_t pidchild, pidwait;
    pidchild = fork();
    switch (pidchild) {
        case -1:
            perror("Error fork");
            exit(EXIT_FAILURE);
        case 0:
            exit(15);
        default:
        pidwait = wait(&estado);
        if (pidwait != -1) {
            if (WIFEXITED(estado)) {
                // WIFEXITED es una macro que comprueba el estado de salida del procesos
                // y devuelve un valor distinto de cero si el proceso ha terminado
                // correctamente. Si el proceso no ha salido correctamente, entonces la macro
                // WIFEEXITED devuelve cero.
            printf("Hijo estado: %d\n", WEXITSTATUS(estado));
            }
        }
    }
    return EXIT_SUCCESS;
}