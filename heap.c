#include <stdio.h>
int main() {
    int n, i, k, j, v, temp, heap;
    printf("Enter no of elements: ");
    if (scanf("%d", &n) != 1) return 1;
    int h[n + 1];
    printf("Enter elements: ");

    for (i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
    }

    // --- Max Heap Construction ---
    for (i = n / 2; i >= 1; i--) {
        k = i;
        v = h[k];
        heap = 0;
        while (!heap && 2 * k <= n) {
            j = 2 * k;
            if (j < n) {
                if (h[j] < h[j + 1]) j = j + 1;
            }
            if (v >= h[j]) {
                heap = 1;
            } else {
                h[k] = h[j];
                k = j;
            }
        }
        h[k] = v;
    }

    // 1. Max Heap print
    printf("Max Heap: ");
    for (i = 1; i <= n; i++) {
        printf("%d ", h[i]);
    }
    printf("\n");

    // Heap Sort (Sorting) ---
    for (i = n; i > 1; i--) {
        temp = h[1];
        h[1] = h[i];
        h[i] = temp;

        k = 1;
        v = h[k];
        heap = 0;
        while (!heap && 2 * k <= (i - 1)) {
            j = 2 * k;
            if (j < (i - 1)) {
                if (h[j] < h[j + 1]) j = j + 1;
            }
            if (v >= h[j]) {
                heap = 1;
            } else {
                h[k] = h[j];
                k = j;
            }
        }
        h[k] = v;
    }


    printf("Sorted Array: ");
    for (i = 1; i <= n; i++) {
        printf("%d ", h[i]);
    }
    printf("\n");

    return 0;
}
