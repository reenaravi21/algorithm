#include <stdio.h>
#include <stdlib.h>

int x[20];

// Board-ai print panna mattum
void printBoard(int n, int k) {
    int i, j;
    printf("\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (i <= k && x[i] == j)
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
}

int place(int k, int i) {
    int j;
    for (j = 1; j < k; j++) {
        if (x[j] == i || abs(x[j] - i) == abs(j - k))
            return 0;
    }
    return 1;
}

int NQueens(int k, int n) {
    int i;
    for (i = 1; i <= n; i++) {
        if (place(k, i)) {
            x[k] = i;

            // Placement message and Board
            printf("\nPlaced Q at Row %d, Column %d", k, i);
            printBoard(n, k);

            if (k == n) {
                printf("\n*** FINAL SOLUTION FOUND ***\n");
                printBoard(n, k); // Final board print
                return 1;
            } else {
                if (NQueens(k + 1, n))
                    return 1;
            }
        }
    }
    return 0;
}

int main() {
    int n;
    printf("Enter no of queens: ");
    scanf("%d", &n);

    if (n > 20) {
        printf("N is too large.\n");
    } else {
        if (!NQueens(1, n)) {
            printf("\nNo solution exists for N=%d\n", n);
        }
    }
    return 0;
}
