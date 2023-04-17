#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int i;
    for (i = 0; i < 3; i++) {
        if (fork() != 0) break;
    }
    // fork();
    // fork();
    // fork();
    
    printf("Soy un proceso\n"); while(1);
}