#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

void *oldhandler;
int signals_sent = 0;
int ascii_code = 0;

void sighandler(int sig){
    signals_sent++;
    char palabra[5] = {'\0'}; // Inicializa la cadena vacía
    int index = 0; // Índice para añadir la letra correspondiente

    if (signals_sent == 72) { // si se recibió la señal correspondiente al código ASCII de la letra 'H'
        ascii_code = 72; // código ASCII de la letra 'H'
        palabra[index] = (char) ascii_code; // convierte el código ASCII a letra y agrega a la cadena
        index++; // incrementa el índice para la siguiente letra
        signals_sent = 0;
    } else if (signals_sent == 111) { // si se recibió la señal correspondiente al código ASCII de la letra 'o'
        ascii_code = 111; // código ASCII de la letra 'o'
        palabra[index] = (char) ascii_code; // convierte el código ASCII a letra y agrega a la cadena
        index++; // incrementa el índice para la siguiente letra
        signals_sent = 0;
    } else if (signals_sent == 108) { // si se recibió la señal correspondiente al código ASCII de la letra 'l'
        ascii_code = 108; // código ASCII de la letra 'l'
        palabra[index] = (char) ascii_code; // convierte el código ASCII a letra y agrega a la cadena
        index++; // incrementa el índice para la siguiente letra
        signals_sent = 0;
    } else if (signals_sent == 97) { // si se recibió la señal correspondiente al código ASCII de la letra 'a'
        ascii_code = 97; // código ASCII de la letra 'a'
        palabra[index] = (char) ascii_code; // convierte el código ASCII a letra y agrega a la cadena
        index++; // incrementa el índice para la siguiente letra
        signals_sent = 0;
    } else {
        printf("Señal %d recibida\n", signals_sent);
        ascii_code = 0; // valor por defecto para señales desconocidas
    }

    if (index == 4) { // si la palabra está completa (4 letras)
    printf("%s\n", palabra); // muestra la palabra completa en la salida estándar
}
}


int main(){
    pid_t pidhijo;
    oldhandler = signal(SIGUSR1, sighandler);
    if(oldhandler == SIG_ERR){
        perror("signal:");
        exit(EXIT_FAILURE);
    }
    
    pidhijo = fork();
    switch(pidhijo){
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
        case 0:
            pause();
            break;
        default:
            int i, j;
            for(i = 0; i < 72; i++){ // se envían 72 señales (código ASCII de 'H')
                kill(pidhijo, SIGUSR1);
                usleep(100);
            }
            for(i = 0; i < 111; i++){ // se envían 111 señales (código ASCII de 'o')
                kill(pidhijo, SIGUSR1);
                usleep(100);
            }
            for(i = 0; i < 108; i++){ // se envían 108 señales (código ASCII de 'l')
                kill(pidhijo, SIGUSR1);
                usleep(100);
            }
            for(i = 0; i < 97; i++){ // se envían 97 señales (código ASCII de 'a')
                kill(pidhijo, SIGUSR1);
                usleep(100);
            }
            printf("[%d]Enviando mensaje: hola\n", getpid());
            wait(NULL);
    }

    if(signal(SIGUSR1, oldhandler) == SIG_ERR){
        perror("signal:");
        exit(EXIT_FAILURE);
    }


    return EXIT_SUCCESS;
}

