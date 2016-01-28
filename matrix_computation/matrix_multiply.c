#include <stdio.h>

#define K 4
#define M 100000

double A[M/K][M];
double X[M][M];
double mid[M/K][M];
double result[M/K][M/K];

int main()
{
    int i = 0;
    int j = 0;
    int k = 0;
    for (i = 0; i < M/K; i++)
        for (j = 0; j < M; j++)
            for (k = 0; k < M; k++)
                mid[i][j] += A[i][k] * X[k][j];
    for (i = 0; i < M/K; i++)
        for (j = 0; j < M/K; j++)
            for (k = 0; k < M; k++)
                result[i][j] += mid[i][k] * A[j][k];
    printf("finished");
    return 0;
}