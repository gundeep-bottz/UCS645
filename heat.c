#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 500        // Grid size (NxN)
#define STEPS 500    // Time steps
#define ALPHA 0.1    // Diffusion constant

int main() {

    static double grid[N][N];
    static double new_grid[N][N];

    // Initialize grid
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            grid[i][j] = 25.0;   // room temperature
        }
    }

    // Heat source in the center
    grid[N/2][N/2] = 100.0;

    double start = omp_get_wtime();

    // Time iteration
    for(int t=0; t<STEPS; t++){

        #pragma omp parallel for collapse(2)
        for(int i=1;i<N-1;i++){
            for(int j=1;j<N-1;j++){
                new_grid[i][j] =
                    grid[i][j] +
                    ALPHA * (
                        grid[i-1][j] +
                        grid[i+1][j] +
                        grid[i][j-1] +
                        grid[i][j+1] -
                        4 * grid[i][j]
                    );
            }
        }

        // Copy new_grid back to grid
        #pragma omp parallel for collapse(2)
        for(int i=1;i<N-1;i++){
            for(int j=1;j<N-1;j++){
                grid[i][j] = new_grid[i][j];
            }
        }
    }

    double end = omp_get_wtime();

    printf("Heat diffusion completed.\n");
    printf("Final center temperature = %f\n", grid[N/2][N/2]);
    printf("Execution Time = %f seconds\n", end - start);

    return 0;
}
