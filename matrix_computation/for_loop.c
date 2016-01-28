#include <stdio.h>

#define K 4
#define M 100000

double X[M][M];
double result[M/K][M/K];

int main()
{
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    for (i = 0; i < M/K; i++)
        for (j = 0; j < M/K; j++)
            for (k = 0; k < K; k++)
                for (l = 0; l < K; l++)
                    result[i][j] += X[i*M/K + k][j*M/K + l];
    return 0;
}