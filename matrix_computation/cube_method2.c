#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE_M 100
#define SIZE_N 256
#define SIZE_O 256
int A[SIZE_M][SIZE_N][SIZE_O];

long SUM1[SIZE_M][SIZE_N][SIZE_O];
long SUM2[SIZE_M][SIZE_N][SIZE_O];

int repeat;
time_t start, end;

int f1, f2, x1, x2, y1, y2;
long result;

int main()
{
    srand(19181716);

    // random create a cube
    int i, j, k;
    for (i = 0; i < SIZE_M; i++)
    {
        for (j = 0; j < SIZE_N; j++)
        {
            for (k = 0; k < SIZE_O; k++)
            {
                A[i][j][k] = rand() % 255;
            }
        }
    }

    // method 2
    /*
    SUM2[0][0][0] = A[0][0][0];
    for (i = 1; i < SIZE_M; i++)
        SUM2[i][0][0] = SUM2[i-1][0][0] + A[i][0][0];
    for (j = 1; j < SIZE_N; j++)
        SUM2[0][j][0] = SUM2[0][j-1][0] + A[0][j][0];
    for (k = 1; k < SIZE_O; k++)
        SUM2[0][0][k] = SUM2[0][0][k-1] + A[0][0][k];
    for (i = 1; i < SIZE_M; i++)
        for (j = 1; j < SIZE_N; j++)
            for (k = 1; k < SIZE_O; k++)
                SUM2[i][j][k] = SUM2[i-1][j][k] + SUM2[i][j-1][k] + SUM2[i][j][k-1]
                                - SUM2[i][j-1][k-1] - SUM2[i-1][j][k-1] - SUM2[i-1][j-1][k]
                                + SUM2[i-1][j-1][k-1] + A[i][j][k];
    */                          
    for (i = 0; i < SIZE_M; i++)
    {
        SUM2[i][0][0] = A[i][0][0];
        for (j = 1; j < SIZE_N; j++)
            SUM2[i][j][0] = SUM2[i][j-1][0] + A[i][j][0];
        for (k = 1; k < SIZE_O; k++)
            SUM2[i][0][k] = SUM2[i][0][k-1] + A[i][0][k];
        for (j = 1; j < SIZE_N; j++)
        {
            for (k = 1; k < SIZE_O; k++)
            {
                SUM2[i][j][k] = SUM2[i][j-1][k] + SUM2[i][j][k-1] - SUM2[i][j-1][k-1] + A[i][j][k];
            }
        }
        if (i > 0)
            for (j = 0; j < SIZE_N; j++)
                for (k = 0; k < SIZE_O; k++)
                {
                    SUM2[i][j][k] = SUM2[i][j][k] + SUM2[i-1][j][k];
                }
    }

    start = clock();
    f1 = 25;
    f2 = 75;
    x1 = 50;
    y1 = 50;
    x2 = 200;
    y2 = 200;
    /*int tmp[] = {SUM2[f2][x2][y2], SUM2[f2][x1-1][y1-1], -SUM2[f2][x1-1][y2], -SUM2[f2][x2][y1-1]
                , -SUM2[f1-1][x2][y2], SUM2[f1-1][x2][y1-1], SUM2[f1-1][x1-1][y2]
                , -SUM2[f1-1][x1-1][y1-1]};*/
    for (repeat = 0; repeat < 100000; repeat++)
    {
        result = SUM2[f2][x2][y2] + SUM2[f2][x1-1][y1-1] - SUM2[f2][x1-1][y2] - SUM2[f2][x2][y1-1]
                - SUM2[f1-1][x2][y2] + SUM2[f1-1][x2][y1-1] + SUM2[f1-1][x1-1][y2]
                - SUM2[f1-1][x1-1][y1-1];
        /* result = 0;
        for (i = 0; i < 8; i++)
        {
            result += tmp[i];
        }*/
    }
    end = clock();
    printf("result = %ld\n", result);
    printf("time for method 2 is: %ld\n", end - start);

    return 0;
}
