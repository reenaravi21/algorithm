#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char data;
    float freq;
    struct Node *left, *right;
};

struct Node *createNode(char data, float freq) {
    struct Node *newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->freq = freq;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void swap(struct Node **a, struct Node **b) {
    struct Node *temp = *a;
    *a = *b;
    *b = temp;
}

void sort(struct Node* arr[], int n) {
    int i, j;
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if (arr[j]->freq > arr[j+1]->freq) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

// Global table to store codes for encoding
char table[256][100];

void storeCodes(struct Node *root, int code[], int top) {
    int i;
    if (root->left) {
        code[top] = 0;
        storeCodes(root->left, code, top + 1);
    }
    if (root->right) {
        code[top] = 1;
        storeCodes(root->right, code, top + 1);
    }
    if (!root->left && !root->right) {
        for (i = 0; i < top; i++) {
            table[(int)root->data][i] = code[i] + '0';
        }
        table[(int)root->data][top] = '\0';
    }
}

void huffman(char data[], float freq[], int n) {
    struct Node* nodes[100];
    int i, size, code[100];
    char inputString[100];

    for(i = 0; i < n; i++) {
        nodes[i] = createNode(data[i], freq[i]);
    }

    size = n;
    while(size > 1) {
        sort(nodes, size);
        struct Node* left = nodes[0];
        struct Node* right = nodes[1];
        struct Node* newNode = createNode('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        nodes[0] = newNode;
        for(i = 1; i < size - 1; i++) {
            nodes[i] = nodes[i+1];
        }
        size--;
    }

    // Generate codes
    storeCodes(nodes[0], code, 0);

    printf("\n------Huffman Codes-------\n");
    for(i = 0; i < n; i++) {
        printf("%c: %s\n", data[i], table[(int)data[i]]);
    }

    // Encoding Part
    printf("\nEnter a string to encode : ");
    scanf("%s", inputString);
    printf("Encoded value: ");
    for(i = 0; i < strlen(inputString); i++) {
        printf("%s", table[(int)inputString[i]]);
    }
    printf("\n");
}

int main() {
    int n, i;
    printf("Enter number of symbols:");
    scanf("%d", &n);
    char data[n];
    float freq[n];
    for(i = 0; i < n; i++) {
        printf("Enter symbol %d:", i + 1);
        scanf(" %c", &data[i]);
        printf("Enter Frequency of %c :", data[i]);
        scanf("%f", &freq[i]);
    }
    huffman(data, freq, n);
    return 0;
}
