#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>


void
init_matrix(int n, double a[n], double maxval)
{
    for (size_t i = 0; i < n * n; i++)
    {
        a[i] = ((double)rand() / (double)RAND_MAX) * maxval;
    }
}

void
transpose(int n, double a[n], double resMpi[n][n], int rank, int nProc)
{
    size_t i = 0, j, idx;
    double rowMpi[n];
    MPI_Request request;
    while (rank + i < n) {
        for (j = 0; j < n; j++)
        {
            idx = j * n + rank + i;
            if (idx < n * n) {
                if (!rank) {
                    resMpi[i][j] = a[idx];

                } else {
                    rowMpi[j] = a[idx];
                }
            }
        }
        if (rank) {
            MPI_Isend(rowMpi, n, MPI_DOUBLE, 0, i, MPI_COMM_WORLD, &request);
        } 
        i += nProc;
    }
}

void
prnmtrx1d(int n, double a[n])
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            printf("%.5f ", a[i * n + j]);
        }
        printf("\n");
    }
    printf("\n");
}

void
prnmtrx2d(int n, double a[n][n])
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            printf("%.5f ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


int main(int argc, char *argv[])
{
    int err;
    if ((err = MPI_Init(&argc, &argv))) {
        MPI_Abort(MPI_COMM_WORLD, err);
    }

    srand(time(NULL));
    double maxval = 10.;
    int nProc, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &nProc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size[10] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000}; //10 for check

    double timerMpi, AverageTime;
    if (!rank) {
        printf("running on %d processes\n", nProc);
        printf("<OUTPUT>\n");
    }

    MPI_Request request;
    for (int i = 0; i < 10; i++) {
        double a[size[i] * size[i]];
        double resMpi[size[i]][size[i]];
        AverageTime = 0.0;
        for (int k = 0; k < 5; k++) {
            if (!rank) {
                init_matrix(size[i], a, maxval);
            }
            
            MPI_Barrier(MPI_COMM_WORLD);
            timerMpi = MPI_Wtime();
            MPI_Bcast(a, size[i] * size[i], MPI_DOUBLE, 0, MPI_COMM_WORLD);
            transpose(size[i], a, resMpi, rank, nProc);
            MPI_Barrier(MPI_COMM_WORLD);
            if (!rank) {
                for (int r = 1; r < nProc; r++) {
                    int proc = 0;
                    while (r + proc < size[i]) {
                        MPI_Irecv(resMpi[r + proc], size[i], MPI_DOUBLE, r, proc, MPI_COMM_WORLD, &request);
                        proc += nProc;
                    }
                }
            }
            MPI_Barrier(MPI_COMM_WORLD);
            AverageTime += MPI_Wtime() - timerMpi;
        }
        AverageTime /= 5.;

        if (!rank) {
            printf("%d,%d,%f\n", size[i], nProc, AverageTime);
        }
    }
    if (!rank) {
        printf("<OUTPUT>");
    }

    MPI_Finalize();
    return 0;
}