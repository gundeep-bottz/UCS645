#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 500        // number of particles
#define EPS 1.0
#define SIGMA 1.0

int main() {

    double x[N], y[N];      // positions
    double fx[N], fy[N];    // forces
    double total_energy = 0.0;

    // Initialize particles
    for (int i = 0; i < N; i++) {
        x[i] = drand48();
        y[i] = drand48();
        fx[i] = 0.0;
        fy[i] = 0.0;
    }

    double start = omp_get_wtime();

    // Parallel computation
    #pragma omp parallel for reduction(+:total_energy)
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {

            double dx = x[i] - x[j];
            double dy = y[i] - y[j];
            double r2 = dx*dx + dy*dy;
            double r = sqrt(r2);

            if (r > 0.0001) {
                double sr6 = pow(SIGMA/r, 6);
                double sr12 = sr6 * sr6;

                // Lennard-Jones potential
                double potential = 4 * EPS * (sr12 - sr6);
                total_energy += potential;

                // Force magnitude
                double f = 24 * EPS * (2*sr12 - sr6) / r2;

                double fxij = f * dx;
                double fyij = f * dy;

                // race condition
                #pragma omp atomic
                fx[i] += fxij;
                #pragma omp atomic
                fy[i] += fyij;
                #pragma omp atomic
                fx[j] -= fxij;
                #pragma omp atomic
                fy[j] -= fyij;
            }
        }
    }

    double end = omp_get_wtime();

    printf("Total Potential Energy = %f\n", total_energy);
    printf("Execution Time = %f seconds\n", end - start);

    return 0;
}
