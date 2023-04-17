#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
int main() {     
    int root = getpid(); 
    /*
             P
           /   \
          /     \
         /       \
        A         B
       / \       / \
      C   D     E   F
         /         / \
        G         H   I
       / \           /
      J   K         L
    */ 
   int i = 0;
    for(int i = 0; i<2; i++) {
        if(fork()==0) {
            if(i==0) {
                int j =0;
                for(j = 0; j<2; j++) {
                    if(fork()==0) {
                        if(j==1) {
                            int k = 0;
                            for(k = 0; k<1; k++) {
                                if(fork()==0) {
                                    int l = 0;
                                    for(l = 0; l<2; l++) {
                                        if(fork()==0) {
                                            break;
                                        }
                                    }
                                    if(l==2)
                                    {
                                        for(l = 0; l<2; l++) {
                                            wait(NULL);
                                        }
                                        printf("Soy el padre y mi pid es %d\n", getpid());
                                    }
                                    break;
                                }
                            }
                            if(k==1)
                            {
                                for(k = 0; k<1; k++) {
                                    wait(NULL);
                                }
                                printf("Soy el padre y mi pid es %d\n", getpid());
                            }
                        }
                        break;
                    }
                }
                if(j==2)
                {
                    for(j = 0; j<2; j++) {
                        wait(NULL);
                    }
                    printf("Soy el padre y mi pid es %d\n", getpid());
                }
                break;
            }
        
            if(i==1) {
                int j = 0;
                for(j = 0; j<2; j++) {
                    if(fork()==0) {
                        if(j==1) {
                            int k = 0;
                            for(k = 0; k<2; k++) {
                                if(fork()==0) {
                                    if(k==1) {
                                        int l = 0;
                                        for(l = 0; l<1; l++) {
                                            if(fork()==0) {
                                                break;
                                            }
                                        }
                                        if(l==1)
                                        {
                                            for(l = 0; l<1; l++) {
                                                wait(NULL);
                                            }
                                            printf("Soy el padre y mi pid es %d\n", getpid());
                                        }
                                    }
                                    break;
                                }
                            }
                            if(k==2)
                            {
                                for(k = 0; k<2; k++) {
                                    wait(NULL);
                                }
                                printf("Soy el padre y mi pid es %d\n", getpid());
                            }
                        }
                        break;
                    }
                }
                if(j==2)
                {
                    for(j = 0; j<2; j++) {
                        wait(NULL);
                    }
                    printf("Soy el padre y mi pid es %d\n", getpid());
                }
            }
        }
    }
    if(root == getpid()) {
        for(i = 0; i<2; i++) {
            wait(NULL);
        }
        printf("Soy el padre y mi pid es %d\n", getpid());
    }

}