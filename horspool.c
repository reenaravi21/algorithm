#include <stdio.h>
#include <string.h>



int main() {
    char text[500], pattern[100];
    int n, m, i, j, p, k, s, sVal;
    int already;

    printf("Enter the Text: ");
    fgets(text, 500, stdin);
    text[strcspn(text, "\n")] = 0;

    printf("Enter the Pattern: ");
    fgets(pattern, 100, stdin);
    pattern[strcspn(pattern, "\n")] = 0;

    n = strlen(text);
    m = strlen(pattern);

    /* 1. LOOKUP TABLE */
    printf("\n SHIFT TABLE \n");
    printf("Char | Shift\n");
    for (j = 0; j < m; j++) {
        already = 0; /* 0 = false */
        for (p = 0; p < j; p++) {
            if (pattern[p] == pattern[j]) already = 1;
        }

        if (!already) {
            s = m;
            for (k = 0; k <= m - 2; k++) {
                if (pattern[k] == pattern[j]) s = m - 1 - k;
            }
            printf("  %c  |   %d\n", pattern[j], s);
        }
    }
    printf("Other|   %d\n", m);

    /* 2. SEARCHING */
    printf("\n SEARCHING\n");
    printf("%s\n", text);

    i = m - 1;
    while (i < n) {
        for (s = 0; s < (i - m + 1); s++) printf(" ");

        k = 0;
        while (k < m && pattern[m - 1 - k] == text[i - k]) {
            k++;
        }

        if (k == m) {
            printf("%s <- MATCH!\n", pattern);
            printf("\nPattern found at index: %d\n", (i - m + 1));
            return 0;
        } else {
            sVal = m;
            for (j = m - 2; j >= 0; j--) {
                if (pattern[j] == text[i]) {
                    sVal = m - 1 - j;
                    break;
                }
            }
            printf("%s (Shift: %d)\n", pattern, sVal);
            i = i + sVal;
        }
    }

    printf("\nPattern not found.\n");
    return 0;
}
