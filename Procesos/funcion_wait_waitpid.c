#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// int main(void) {
//     pid_t pidchild = fork();
//     switch (pidchild) {
//         case -1:
//             perror("Error fork");
//             exit(EXIT_FAILURE);
//             break;
//         case 0: 
//             printf("P. hijo: pid=%d y pppid=%d\n", getpid(), getppid());
//             break;
//         default:
//             printf("P.Padre: pid=%d y ppid=%d\n", getpid(), getppid());
//             wait(NULL);
//     }
//     return EXIT_SUCCESS;
// }

int main(void) {
    pid_t root = getpid();

    for (int i = 0; i < 3; i++) {
        if (fork() == 0) 
            break;
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