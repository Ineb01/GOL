

/*
 * File:   main.c
 * Author: Benjamin Bachmayr
 *
 * Created on 24. November 2016, 20:18
 */

#include <stdio.h>
#include <stdlib.h>

void* PrintThread();
void GetNeighbours();
void UpdateCells();
int xsize = 3;
int ysize = 3;
int sleep = 100;
int mode = 0;

int rgMain[100][100] = {0};

int rgNeighbours[100][100] = {0};

int main(int argc, char** argv) {

    int x, y;
    int i = 1;
    char temp;

    pthread_t threads[ 1 ];
    int thread_args[ 1 ];
    int result_code;
    thread_args[ 0 ] = 0;
    result_code = pthread_create(threads, NULL, PrintThread, thread_args);
    FILE *fp;

    fp = fopen("Pattern.txt", "r");

    while (i) {

        fscanf(fp, "%c", &temp);

        switch (temp) {

            case'S':    fscanf(fp, "%d", &xsize);
                        fscanf(fp, "%d", &ysize);
                        break;

            case'P':    for (x = 0; x < xsize; x++) {
                            for (y = 0; y < ysize; y++) {
                                fscanf(fp, "%d", &rgMain[x][y]);
                            }
                        }
                        break;

            case'D':    fscanf(fp, "%d", &sleep);
                        sleep = sleep * 1000;
                        break;

            case'M':    fscanf(fp, "%d", &mode);
                        break;

            case';':    i = 0;
                        break;

        }

    }

    fclose(fp);

    printf("\e[?25l");

    while (1) {
        UpdateCells();
        usleep(sleep);
    }


    return (EXIT_SUCCESS);
}

void* PrintThread() {

    int x, y;
    int i;


    while (1) {
        printf("\033[%d;%dH", 0, 0);

        printf(" ");

        for (i = 0; i < xsize; i++) {

            printf("_");

        }

        printf("\n|");

        for (x = 0; x < xsize; x++) {
            for (y = 0; y < ysize; y++) {
                if (rgMain[x][y])printf("#");
                else printf(" ");
            }

            if (x != xsize - 1) {

                printf("|\n|");

            } else {

                printf("|\n");

            }

        }

        printf("|");

        for (i = 0; i < xsize; i++) {

            printf("_");

        }

        printf("|");


        /*        printf("\n");
                for (x = 0; x < xsize; x++) {
                    for (y = 0; y < ysize; y++) {
                        printf("%d", rgNeighbours[x][y]);
                    }
                    printf("\n");
                }
                usleep(sleep); komplexe zahlen statistische fehler
         */
    }
}

void GetNeighbours() {

    int x, y;

    for (x = 0; x < xsize; x++) {
        for (y = 0; y < ysize; y++) {

            rgNeighbours[x][y] = 0;

        }
    }

    for (x = 0; x < xsize; x++) {
        for (y = 0; y < ysize; y++) {

            if (rgMain[(x + 1) % xsize][y] == 1) {

                rgNeighbours[x][y] = rgNeighbours[x][y] + 1;

            }

            if (rgMain[(x - 1 + xsize) % xsize][y] == 1) {

                rgNeighbours[x][y] = rgNeighbours[x][y] + 1;

            }

            if (rgMain[x][(y + 1) % ysize] == 1) {

                rgNeighbours[x][y] = rgNeighbours[x][y] + 1;

            }

            if (rgMain[x][(y - 1 + ysize) % ysize] == 1) {

                rgNeighbours[x][y] = rgNeighbours[x][y] + 1;

            }

            if (rgMain[(x + 1) % xsize][(y + 1) % ysize] == 1) {

                rgNeighbours[x][y] = rgNeighbours[x][y] + 1;

            }

            if (rgMain[(x - 1 + xsize) % xsize][(y - 1 + ysize) % ysize] == 1) {

                rgNeighbours[x][y] = rgNeighbours[x][y] + 1;

            }

            if (rgMain[(x + 1) % xsize][(y - 1 + ysize) % ysize] == 1) {

                rgNeighbours[x][y] = rgNeighbours[x][y] + 1;

            }

            if (rgMain[(x - 1 + xsize) % xsize][(y + 1) % ysize] == 1) {

                rgNeighbours[x][y] = rgNeighbours[x][y] + 1;

            }

        }

    }


}

void UpdateCells() {
    int x, y;

    GetNeighbours();

    for (x = 0; x < xsize; x++) {
        for (y = 0; y < ysize; y++) {

            if (rgNeighbours[x][y] == 3) {

                rgMain[x][y] = 1;

            }

            if (rgNeighbours[x][y] < 2) {

                rgMain[x][y] = 0;

            }

            if (rgNeighbours[x][y] > 3) {

                rgMain[x][y] = 0;

            }
        }
    }
}

