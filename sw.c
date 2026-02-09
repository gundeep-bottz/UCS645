#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define MATCH  2
#define MISMATCH -1
#define GAP   -1

int max(int a, int b, int c, int d) {
    int m = a;
    if (b > m) m = b;
    if (c > m) m = c;
    if (d > m) m = d;
    return m;
}

int main() {

    char seq1[] = "ACACACTA";
    char seq2[] = "AGCACACA";

    int n = strlen(seq1);
    int m = strlen(seq2);

    int H[n+1][m+1];

    // Initialize matrix
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++)
            H[i][j]=0;

    double start = omp_get_wtime();

    int max_score = 0;

    // Wavefront parallelization (diagonal-wise)
    for(int k=1; k<=n+m; k++) {
        #pragma omp parallel for
        for(int i=1;i<=n;i++) {
            int j = k - i;
            if(j>=1 && j<=m) {

                int score;
                if(seq1[i-1]==seq2[j-1])
                    score = MATCH;
                else
                    score = MISMATCH;

                int val = max(
                    0,
                    H[i-1][j-1] + score,
                    H[i-1][j] + GAP,
                    H[i][j-1] + GAP
                );

                H[i][j] = val;

                #pragma omp critical
                {
                    if(val > max_score)
                        max_score = val;
                }
            }
        }
    }

    double end = omp_get_wtime();

    printf("Best Alignment Score = %d\n", max_score);
    printf("Execution Time = %f seconds\n", end-start);

    return 0;
}
