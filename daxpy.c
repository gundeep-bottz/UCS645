#include<stdio.h>
#include<omp.h>

int main()
{
    int i;
    int n = 65536;
    double a = 2.0;
    double X[65536];
    double Y[65536];

    for(i=0;i<n;i++)
    {
        X[i] = 1.0;
        Y[i] = 2.0;
    }

    double start = omp_get_wtime();

    #pragma omp parallel for
    for(i=0;i<n;i++)
    {
        X[i] = a*X[i] + Y[i];
    }

    double end = omp_get_wtime();

    printf("Time = %f\n", end-start);

    return 0;
}
