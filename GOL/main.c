

/*
 * File:   main.c
 * Author: Benjamin Bachmayr
 *
 * Created on 24. November 2016, 20:18
 */

#include <stdio.h>
#include <stdlib.h>

#define XSIZE 7
#define YSIZE 7
#define SLEEP 100 * 1000

void* PrintThread();
void  GetNeighbours();
void  UpdateCells();

int rgMain[XSIZE][YSIZE] = {0, 0, 1, 0, 0, 0, 0,
                            0, 0, 0, 1, 0, 0, 0,
                            0, 1, 1, 1, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0};

int rgNeighbours[XSIZE][YSIZE] = {0};

int main(int argc, char** argv) {

    pthread_t threads[ 1 ];
    int thread_args[ 1 ];
    int result_code;
    thread_args[ 0 ] = 0;
    result_code = pthread_create(threads, NULL, PrintThread, thread_args);
   
    printf("\e[?25l");
   
    while(1){
        GetNeighbours();
        UpdateCells();
        usleep(SLEEP);
    }
   
   
    return (EXIT_SUCCESS);
}

void* PrintThread() {
   
    int x, y;
    int i;
    
        
    while (1) {
        printf("\033[%d;%dH", 0, 0);
        
        printf("â");
    
        for(i = 0; i < XSIZE; i++){
        
            printf("â");
        
        }
    
        printf("â\n|");
        
        for (x = 0; x < XSIZE; x++) {
            for (y = 0; y < YSIZE; y++) {
                if (rgMain[x][y])printf("#");
                else printf(" ");
            }
            
            if(x != XSIZE - 1){
                
                printf("â\nâ");
                
            }else{
                
                printf("â\n");
                
            }
            
        }
        
        printf("â");
    
        for(i = 0; i < XSIZE; i++){
        
            printf("â");
        
        }
    
        printf("â");
       
       
/*        printf("\n");
        for (x = 0; x < XSIZE; x++) {
            for (y = 0; y < YSIZE; y++) {
                printf("%d", rgNeighbours[x][y]);
            }
            printf("\n");
        }
        usleep(SLEEP); komplexe zahlen statistische fehler
 */
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

