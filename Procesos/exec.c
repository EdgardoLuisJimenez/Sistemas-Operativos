#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wait.h>

int main() {

    if (!fork()) {
        printf("Control1\n");
        execlp("/usr/bin/ls", "ls", "-a", "-l", NULL);
        printf("Control2");
        return EXIT_SUCCESS;
    }
    else {
        printf("Soy padre");
        wait(NULL);
    }

    
}