#include<stdio.h>
#include<omp.h>

int main()
{
    int i;
    long steps = 1000000;
    double step, x, sum = 0.0, pi;

    step = 1.0 / steps;

    double start = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for(i=0;i<steps;i++)
    {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x*x);
    }

    pi = step * sum;

    double end = omp_get_wtime();

    printf("PI = %f\n", pi);
    printf("Time = %f\n", end-start);

    return 0;
}
