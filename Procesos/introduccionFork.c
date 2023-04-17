#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> //Funcion fork disponible en esta libreria

int main(void) {
    pid_t pidchild = fork();

    switch (pidchild) {
        case -1: /* Error, majerar el error */
            perror("Error fork");
            exit(EXIT_FAILURE);
            break;
        case 0: /* Bloque proceso hijo */
            printf("Proceso hijo\n");
            break;
        default: /* Bloque proceso padre */
            printf("Proceso padre\n");
    }
    return 0;
}