#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

    pid_t root = getpid();

    for (int i = 0; i < 3; i++) {
        if (fork() == 0) {
            if (i == 0 || i == 2) {
                fork();
                for (int k = 0; k < 1; k++) {
                    wait(NULL);
                }
            }
            break;
        }
    }

    if (root == getpid()) {  
        for (int j = 0; j < 3; j++) 
            wait(NULL); // Con la condicion NULL especifica que no necesita informacion
            // sobre el estado de los procesos hijos.
        printf("Finalizando padre %d\n", getpid());
        
    }
    else
        printf("Finalizando hijo%d\n", getpid());
    return EXIT_SUCCESS;
}