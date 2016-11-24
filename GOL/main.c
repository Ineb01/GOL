/* 
 * File:   main.c
 * Author: Benjamin Bachmayr
 *
 * Created on 24. November 2016, 20:18
 */

#include <stdio.h>
#include <stdlib.h>

#define XSIZE 3
#define YSIZE 3

void* PrintThread();

int rgMain[XSIZE][YSIZE] = {1, 0, 0,
                            0, 1, 0,
                            1, 0, 1};

int main(int argc, char** argv) {

    pthread_t threads[ 1 ];
    int thread_args[ 1 ];
    int result_code;
    thread_args[ 0 ] = 0;
    result_code = pthread_create(threads, NULL, PrintThread, thread_args);

    while(1){
        sleep(10);
    }
    
    
    return (EXIT_SUCCESS);
}

void* PrintThread() {
    int x, y;
    while (1) {
        printf("\033[%d;%dH", 0, 0);
        for (x = 0; x < XSIZE; x++) {
            for (y = 0; y < YSIZE; y++) {
                if (rgMain[x][y])printf("#");
                else printf(" ");
            }
            printf("\n");
        }
        sleep(1);
    }
}
