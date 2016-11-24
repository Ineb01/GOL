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
void  GetNeighbours();
void  UpdateCells();

int rgMain[XSIZE][YSIZE] = {0, 0, 0,
                            1, 1, 1,
                            0, 0, 0};

int rgNeighbours[XSIZE][YSIZE] = {0};

int main(int argc, char** argv) {

    pthread_t threads[ 1 ];
    int thread_args[ 1 ];
    int result_code;
    thread_args[ 0 ] = 0;
    result_code = pthread_create(threads, NULL, PrintThread, thread_args);
        
    while(1){
        GetNeighbours();
        UpdateCells();
        sleep(1);
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
        printf("\n");
        for (x = 0; x < XSIZE; x++) {
            for (y = 0; y < YSIZE; y++) {
                printf("%d", rgNeighbours[x][y]);
            }
            printf("\n");
        }
        sleep(1);
    }
}

void  GetNeighbours(){
    
    int x,y;
    
    for(x = 0; x < XSIZE; x ++){
        for(y = 0; y < YSIZE; y++){ 
            
            rgNeighbours[x][y] = 0;
            
        }
    }    
    
    for(x = 0; x < XSIZE; x ++){
        for(y = 0; y < YSIZE; y++){ 
        
            if(rgMain[(x + 1) % XSIZE][y] == 1){
                
                rgNeighbours[x][y] = rgNeighbours[x][y] + 1;
                
            }
        
            if(rgMain[(x - 1 + XSIZE) % XSIZE][y] == 1){
                
                rgNeighbours[x][y] = rgNeighbours[x][y] + 1;
                
            }
        
            if(rgMain[x][(y + 1) % YSIZE] == 1){
                
                rgNeighbours[x][y] = rgNeighbours[x][y] + 1;
                
            }
        
            if(rgMain[x][(y - 1 + YSIZE) % YSIZE] == 1){
                
                rgNeighbours[x][y] = rgNeighbours[x][y] + 1;
                
            }
        
            if(rgMain[(x + 1) % XSIZE][(y + 1) % YSIZE] == 1){
                
                rgNeighbours[x][y] = rgNeighbours[x][y] + 1;
                
            }
        
            if(rgMain[(x - 1 + XSIZE) % XSIZE][(y - 1 + YSIZE) % YSIZE] == 1){
                
                rgNeighbours[x][y] = rgNeighbours[x][y] + 1;
                
            }
        
            if(rgMain[(x + 1) % XSIZE][(y - 1 + YSIZE) % YSIZE] == 1){
                
                rgNeighbours[x][y] = rgNeighbours[x][y] + 1;
                
            }
        
            if(rgMain[(x - 1 + XSIZE) % XSIZE][(y + 1) % YSIZE] == 1){
                
                rgNeighbours[x][y] = rgNeighbours[x][y] + 1;
                
            }
            
        }
        
    }
    
    
}

void  UpdateCells(){
    int x,y;
    
    for(x = 0; x < XSIZE; x ++){
        for(y = 0; y < YSIZE; y++){ 
            
            if(rgNeighbours[x][y] == 3){
                
                rgMain[x][y] = 1;
                
            }
            
            if(rgNeighbours[x][y] < 2){
                
                rgMain[x][y] = 0;
                
            }
            
            if(rgNeighbours[x][y] > 3){
                
                rgMain[x][y] = 0;
                
            }            
        }
    }    
}