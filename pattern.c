#include <stdio.h>

int main() {
    char text[100], pattern[50];
    int n = 0, m = 0;
    int i, j, pos = -1;

    printf("Enter text: ");
    scanf("%[^\n]%*c", text);

    printf("Enter pattern: ");
    scanf("%[^\n]%*c", pattern);


    while (text[n] != '\0') {
        n++;
    }


    while (pattern[m] != '\0') {
        m++;
    }


    for (i = 0; i <= n - m; i++) {
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == m) {
            pos = i;
            break;
        }
    }

    if (pos != -1)
        printf("Pattern found at index %d\n", pos);
    else
        printf("Pattern not found\n");

    return 0;
}
