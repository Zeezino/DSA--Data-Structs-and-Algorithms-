#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define INFINITE INT_MAX

void push(int **C, int **F, int *excess, int u, int v) {
    int send = MIN(excess[u], C[u][v] - F[u][v]);
    F[u][v] += send;
    F[v][u] -= send;
    excess[u] -= send;
    excess[v] += send;
}

void relabel(int **C, int **F, int *height, int u, int nodes) {
    int min_height = INFINITE;
    for (int v = 0; v < nodes; v++) {
        if (C[u][v] - F[u][v] > 0) {
            min_height = MIN(min_height, height[v]);
        }
    }
    if (min_height < INFINITE) {
        height[u] = min_height + 1;
    }
}

void discharge(int **C, int **F, int *excess, int *height, int *seen, int u, int nodes) {
    while (excess[u] > 0) {
        if (seen[u] < nodes) {
            int v = seen[u];
            if ((C[u][v] - F[u][v] > 0) && (height[u] > height[v])) {
                push(C, F, excess, u, v);
            } else {
                seen[u]++;
            }
        } else {
            relabel(C, F, height, u, nodes);
            seen[u] = 0;
        }
    }
}

int pushRelabel(int **C, int **F, int source, int sink, int nodes) {
    int *excess = calloc(nodes, sizeof(int));
    int *height = calloc(nodes, sizeof(int));
    int *seen = calloc(nodes, sizeof(int));
    int *list = malloc((nodes-2) * sizeof(int));

    // Create list of nodes excluding source and sink
    int p = 0;
    for (int i = 0; i < nodes; i++) {
        if (i != source && i != sink) {
            list[p++] = i;
        }
    }

    height[source] = nodes;
    excess[source] = INFINITE;

    // Initial push from source
    for (int i = 0; i < nodes; i++) {
        push(C, F, excess, source, i);
    }

    p = 0;
    while (p < nodes - 2) {
        int u = list[p];
        int old_height = height[u];
        discharge(C, F, excess, height, seen, u, nodes);
        if (height[u] > old_height) {
            // Move to front
            int temp = list[p];
            for (int i = p; i > 0; i--) {
                list[i] = list[i-1];
            }
            list[0] = temp;
            p = 0;
        } else {
            p++;
        }
    }

    int maxflow = 0;
    for (int i = 0; i < nodes; i++) {
        maxflow += F[i][sink];
    }

    free(excess);
    free(height);
    free(seen);
    free(list);

    return maxflow;
}

int main() {
    const int n = 6;
    
    // Initialize capacity and flow matrices
    int **capacity = malloc(n * sizeof(int*));
    int **flow = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        capacity[i] = calloc(n, sizeof(int));
        flow[i] = calloc(n, sizeof(int));
    }

    // Set up edges
    capacity[0][1] = 2;
    capacity[0][2] = 9;
    capacity[1][2] = 1;
    capacity[2][4] = 7;
    capacity[4][5] = 4;
    capacity[5][3] = 7;

    int source = 0;
    int sink = 3;
    
    int max_flow = pushRelabel(capacity, flow, source, sink, n);
    printf("Maximum flow: %d\n", max_flow);

    // Cleanup
    for (int i = 0; i < n; i++) {
        free(capacity[i]);
        free(flow[i]);
    }
    free(capacity);
    free(flow);

    return 0;
}