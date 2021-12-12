#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

double omp_get_wtime(void);

double **
init_matrix(int n, int m, double maxval)
{
    double **a = malloc(sizeof(double *) * n);
    for (size_t i = 0; i < n; i++)
    {
        a[i] = malloc(sizeof(double) * m);
        for (size_t j = 0; j < m; j++)
        {
            a[i][j] = ((double)rand() / (double)RAND_MAX) * maxval;
        }
    }
    return a;
}

double **
transpose(double **a, int n, int m, int nThreads)
{
    double **b = malloc(sizeof(double *) * m);
    int i, j;
#pragma omp parallel for private(i, j) shared(a, b) num_threads(nThreads)
    for (i = 0; i < m; i++)
    {
        b[i] = malloc(sizeof(double) * n);
        for (j = 0; j < n; j++)
        {
            b[i][j] = a[j][i];
        }
    }
    return b;
}

void prnmtrx(double **a, int n, int m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            printf("%.5f ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void freemtrx(double **a, int n)
{
    for (size_t i = 0; i < n; i++)
    {
        free(a[i]);
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    double **a;
    int n[10] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    int nThread[7] = {1, 2, 4, 8, 16, 32, 64};
    double timerOpenMp, AverageTime;
    double maxval = 10.;
    printf("size\tn_thread\taverage_time\n");
    for (int i = 0; i < 10; i++)
    {
        a = init_matrix(n[i], n[i], maxval);
        for (int j = 0; j < 7; j++)
        {
            AverageTime = 0;
            for (int k = 0; k < 5; k++) {
                timerOpenMp = omp_get_wtime();
                a = transpose(a, n[i], n[i], nThread[j]);
                AverageTime += omp_get_wtime() - timerOpenMp;
            }
            AverageTime /= 5.;
            printf("%d\t%d\t%f\n", n[i], nThread[j], AverageTime);

        }
        freemtrx(a, n[i]);
    }
    return 0;
}
