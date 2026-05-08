#include <stdio.h>

int main() {
    int n, i, j, v, k;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    int a[n];
    printf("Enter elements:\n");

    for (k = 0; k < n; k++) {
        scanf("%d", &a[k]);
    }
    for (i = 1; i <= n - 1; i++) {
        v = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > v) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = v;
    }

    printf("\nSorted array: ");
    for (k = 0; k < n; k++) {
        printf("%d ", a[k]);
    }    printf("\n");

    return 0;
}
