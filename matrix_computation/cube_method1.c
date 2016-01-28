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


    // method 1

    for (i = 0; i < SIZE_M; i++)
    {
        SUM1[i][0][0] = A[i][0][0];
        for (j = 1; j < SIZE_N; j++)
            SUM1[i][j][0] = SUM1[i][j-1][0] + A[i][j][0];
        for (k = 1; k < SIZE_O; k++)
            SUM1[i][0][k] = SUM1[i][0][k-1] + A[i][0][k];
        for (j = 1; j < SIZE_N; j++)
        {
            for (k = 1; k < SIZE_O; k++)
            {
                SUM1[i][j][k] = SUM1[i][j-1][k] + SUM1[i][j][k-1] - SUM1[i][j-1][k-1] + A[i][j][k];
            }
        }
    }
    f1 = 25;
    f2 = 75;
    x1 = 50;
    y1 = 50;
    x2 = 200;
    y2 = 200;
    start = clock();
    for (repeat = 0; repeat < 100000; repeat++)
    {
        result = 0;
        for (i = f1; i <= f2; i++)
        {
            result = result + SUM1[i][x2][y2] - SUM1[i][x2][y1-1] - SUM1[i][x1-1][y2] + SUM1[i][x1-1][y1-1];
        }
    }
    end = clock();
    printf("result = %ld\n", result);
    printf("time for method 1 is: %ld\n", end - start);

    return 0;
}
