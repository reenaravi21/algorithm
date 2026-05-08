#include <stdio.h>
#include <math.h>
#include <float.h>

int main() {
    int n, i, j;
    float d = FLT_MAX;
    float x[50], y[50], distance;
    int p1 = 0, p2 = 0;

    printf("Enter number of points: ");
    scanf("%d", &n);

    printf("Enter x and y coordinates:\n");
    for(i = 0; i < n; i++) {
        scanf("%f %f", &x[i], &y[i]);
    }

    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            distance = sqrt((x[i] - x[j]) * (x[i] - x[j]) +
                            (y[i] - y[j]) * (y[i] - y[j]));
            if(distance < d) {
                d = distance;
                p1 = i;
                p2 = j;
            }
        }
    }

    printf("Minimum distance = %.2f\n", d);
    printf("Closest pair: (%.2f, %.2f) and (%.2f, %.2f)\n", x[p1], y[p1], x[p2], y[p2]);

    return 0;
}
