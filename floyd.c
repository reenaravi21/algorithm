#include <stdio.h>

#define INF 999 /* Infinity value */

int main() {
    int n, i, j, k;
    int dist[20][20];

    // 1. Get Number of Vertices
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    // 2. Get the Adjacency Matrix
    // Note: Use 999 for infinity (no direct edge)
    printf("Enter the adjacency matrix (use 999 for infinity):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
        }
    }

    // 3. Floyd's Algorithm Core Logic
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                // If path through k is shorter, update it
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // 4. Print the Final Result
    printf("\nShortest path matrix (Result):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (dist[i][j] >= INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }

    return 0;
}
