#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include<wait.h>
int main(int argc, char){
    pid_t pidp = getpid();
    pid_t* pidsh = (pid_t*) malloc(sizeof(pid_t)*2);
    pid_t* pidsn = (pid_t*) malloc(sizeof(pid_t)*2);
    pidsh[0]= -1;
    pidsh[1]= -1;
    pidsn[0]= -1;
    pidsn[1]= -1;
    void * oldhandler1;
    int n;
    printf("cuantas veces desea recorrer el ciclo?: ");
    scanf("%d",&n);
    void sighandler1( int sig ){
    
    }
    void sighandler2( int sig ){
    
    }
    oldhandler1 = signal( SIGUSR1, sighandler1); 
    if(oldhandler1 == SIG_ERR){perror("signal:");exit(EXIT_FAILURE);  }
    int i;
    for(i=0; i<2;i++){
        pidsh[i]=fork();
        if(pidsh[i]== 0 ){
            pidsn[i] = fork();
            break;
        }
    }
    if(pidp == getpid() && i ==2){
        usleep(100);
        printf("padre [%d]\n",getpid());
        for(int j = 0;j<n;j++){
            printf("-----------------------------------------------------------\n");
            kill(pidsh[1],SIGUSR1);
            pause();
            printf("padre [%d]\n",getpid());
        }
        for(int l = 0;l<2;l++){
            wait(NULL);
        }
        printf("termino el programa padre. \n");
    }
    else{
        if(pidsh[1] == 0 && getppid()==pidp && pidsn[1] != 0){
            for(int j = 0;j<n;j++){
                pause();
                printf("hijo [%d]\n",getpid());
                kill(pidsn[1],SIGUSR1);
                pause();
                printf("hijo [%d]\n",getpid());
                kill(pidsh[0],SIGUSR1);
            }
            wait(NULL);
        }else{
            if(pidsh[0] == 0 && getppid()==pidp && pidsn[0] != 0){
                for(int j = 0;j<n;j++){
                    pause();
                    printf("hijo [%d]\n",getpid());
                    kill(pidsn[0],SIGUSR1);
                    pause();
                    printf("hijo [%d]\n",getpid());
                    kill(getppid(),SIGUSR1);
                }
                wait(NULL);
            }else{
                if(pidsn[1] == 0 && getppid()!= pidp && pidsn[0] != 0 ){
                    for(int j = 0;j<n;j++){
                        pause();
                        printf("nieto [%d]\n",getpid());
                        kill(getppid(),SIGUSR1);
                    }
                }else{
                    if(pidsn[0] == 0 && getppid()!= pidp){
                        for(int j = 0;j<n;j++){
                            pause();
                            printf("nieto [%d]\n",getpid());
                            kill(getppid(),SIGUSR1);
                        }
                    }
                }
            }
        }
    }
    if(signal(SIGUSR1, oldhandler1) == SIG_ERR){
        perror("signal:");
        exit(EXIT_FAILURE);
    }
    return 0;
}