#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>

int main() {      
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
    for(int i = 0; i<2; i++) {
        if(fork()==0) {
            if(i==0) {
                for(int j = 0; j<2; j++) {
                    if(fork()==0) {
                        if(j==1) {
                            for(int k = 0; k<1; k++) {
                                if(fork()==0) {
                                    for(int l = 0; l<2; l++) {
                                        if(fork()==0) {
                                            break;
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
                break;
            }
        
            if(i==1) {
                for(int j = 0; j<2; j++) {
                    if(fork()==0) {
                        if(j==1) {
                            for(int k = 0; k<2; k++) {
                                if(fork()==0) {
                                    if(k==1) {
                                        for(int l = 0; l<1; l++) {
                                            if(fork()==0) {
                                                break;
                                            }
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    return EXIT_SUCCESS;
}