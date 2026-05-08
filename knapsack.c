#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Global arrays for item data */
int id[50], weight[50], value[50];
double ratio[50];

/* Global arrays for node tracking */
int levelArr[200], weightArr[200], valueArr[200], parent[200];
double boundArr[200];
bool included[200];

typedef struct {
    int index;
    double bound;
} Node;

/* --- Priority Queue (Max-Heap) Implementation --- */
Node heap[200];
int heapSize = 0;

void push(Node n) {
    int i = heapSize++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p].bound >= n.bound) break;
        heap[i] = heap[p];
        i = p;
    }
    heap[i] = n;
}

Node pop() {
    Node res = heap[0];
    Node last = heap[--heapSize];
    int i = 0, child;
    while (i * 2 + 1 < heapSize) {
        child = i * 2 + 1;
        if (child + 1 < heapSize && heap[child + 1].bound > heap[child].bound) child++;
        if (last.bound >= heap[child].bound) break;
        heap[i] = heap[child];
        i = child;
    }
    heap[i] = last;
    return res;
}

double getBound(int level, int w, int v, int n, int W) {
    int j, totalWeight;
    double profit;
    if (w >= W) return 0;
    profit = v;
    j = level + 1;
    totalWeight = w;

    while (j < n && totalWeight + weight[j] <= W) {
        totalWeight += weight[j];
        profit += value[j];
        j++;
    }
    if (j < n) {
        profit += (double)(W - totalWeight) * ratio[j];
    }
    return profit;
}

int main() {
    int n, W, i, j, trace, pSize, path[50];
    int nodeCount = 0, maxProfit = 0, bestNode = 0;
    Node root;

    printf("Enter number of items: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        id[i] = i + 1;
        printf("Item %d weight: ", i + 1);
        scanf("%d", &weight[i]);
        printf("Item %d value: ", i + 1);
        scanf("%d", &value[i]);
        ratio[i] = (double)value[i] / weight[i];
    }

    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    /* Sort items by Ratio */
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (ratio[i] < ratio[j]) {
                double tr = ratio[i]; ratio[i] = ratio[j]; ratio[j] = tr;
                int tw = weight[i]; weight[i] = weight[j]; weight[j] = tw;
                int tv = value[i]; value[i] = value[j]; value[j] = tv;
                int ti = id[i]; id[i] = id[j]; id[j] = ti;
            }
        }
    }

    printf("\nSorted Items:\nItem Weight Value Ratio\n");
    for (i = 0; i < n; i++) {
        printf("%d     %d     %d     %.2f\n", id[i], weight[i], value[i], ratio[i]);
    }

    /* Root Node Initialization */
    levelArr[0] = -1;
    weightArr[0] = 0;
    valueArr[0] = 0;
    boundArr[0] = getBound(-1, 0, 0, n, W);
    parent[0] = -1;
    included[0] = false;

    root.index = 0;
    root.bound = boundArr[0];
    push(root);

    printf("\n===== Branch and Bound =====\n");

    while (heapSize > 0) {
        Node current = pop();
        int u = current.index;
        int nextLevel, v_inc, v_exc;

        if (boundArr[u] < maxProfit) continue;

        nextLevel = levelArr[u] + 1;
        if (nextLevel >= n) continue;

        /* Left Child (Include) */
        nodeCount++;
        v_inc = nodeCount;
        levelArr[v_inc] = nextLevel;
        weightArr[v_inc] = weightArr[u] + weight[nextLevel];
        valueArr[v_inc] = valueArr[u] + value[nextLevel];
        parent[v_inc] = u;
        included[v_inc] = true;

        if (weightArr[v_inc] <= W) {
            if (valueArr[v_inc] > maxProfit) {
                maxProfit = valueArr[v_inc];
                bestNode = v_inc;
            }
            boundArr[v_inc] = getBound(nextLevel, weightArr[v_inc], valueArr[v_inc], n, W);
            if (boundArr[v_inc] >= maxProfit) {
                Node temp;
                temp.index = v_inc; temp.bound = boundArr[v_inc];
                push(temp);
            }
        }

        /* Right Child (Exclude) */
        nodeCount++;
        v_exc = nodeCount;
        levelArr[v_exc] = nextLevel;
        weightArr[v_exc] = weightArr[u];
        valueArr[v_exc] = valueArr[u];
        parent[v_exc] = u;
        included[v_exc] = false;

        boundArr[v_exc] = getBound(nextLevel, weightArr[v_exc], valueArr[v_exc], n, W);
        if (boundArr[v_exc] >= maxProfit) {
            Node temp;
            temp.index = v_exc; temp.bound = boundArr[v_exc];
            push(temp);
        }
    }

    printf("\nOptimal Value = %d\n", maxProfit);
    printf("Items included in optimal solution: ");

    pSize = 0;
    trace = bestNode;
    while (trace != 0) {
        if (included[trace]) path[pSize++] = id[levelArr[trace]];
        trace = parent[trace];
    }
    for (i = pSize - 1; i >= 0; i--) printf("%d ", path[i]);
    printf("\n");

    return 0;
}
