#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// โครงสร้างข้อมูลสำหรับแทนเส้นเชื่อมในกราฟ
struct Edge {
    int src, dest, weight;
};

// โครงสร้างข้อมูลสำหรับแทนกราฟ
struct Graph {
    int V, E;
    struct Edge* edges;
};

// โครงสร้างข้อมูลสำหรับตัวแทนเซต (Subset)
struct Subset {
    int parent;
    int rank;
};

// ฟังก์ชันสร้างกราฟ
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

// ฟังก์ชันสร้าง Subset
struct Subset* createSubsets(int V) {
    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));
    for (int i = 0; i < V; ++i) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }
    return subsets;
}

// ฟังก์ชันหาเซตของตัวแทน (Path Compression)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// ฟังก์ชันเชื่อมตัวแทนสองเซต (Union by Rank)
void unionSets(struct Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank) {
        subsets[rootX].parent = rootY;
    } else if (subsets[rootX].rank > subsets[rootY].rank) {
        subsets[rootY].parent = rootX;
    } else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// ฟังก์ชันสำหรับ Prim's Algorithm
void primMST(struct Graph* graph) {
    int V = graph->V;
    int parent[V];
    int key[V];
    int inMST[V];

    for (int i = 0; i < V; ++i) {
        key[i] = INT_MAX;
        inMST[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; ++count) {
        int u, minKey = INT_MAX;
        for (int v = 0; v < V; ++v) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        inMST[u] = 1;

        for (int v = 0; v < V; ++v) {
            int weight = graph->edges[u * V + v].weight;
            if (weight && !inMST[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
        }
    }

    printf("Minimum Spanning Tree (Prim):\n");
    for (int i = 1; i < V; ++i) {
        printf("%d - %d\n", parent[i], i);
    }
}
// ฟังก์ชันสำหรับเปรียบเทียบ
int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}


//ฟังก์ชันสำหรับ Kruskal's Algorithm
void kruskalMST(struct Graph* graph) {
    int V = graph->V;
    int E = graph->E;

    struct Edge result[V - 1];

    qsort(graph->edges, E, sizeof(graph->edges[0]), compareEdges);

    struct Subset* subsets = createSubsets(V);

    int i = 0, e = 0;
    while (e < V - 1) {
        struct Edge nextEdge = graph->edges[i++];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        if (x != y) {
            result[e++] = nextEdge;
            unionSets(subsets, x, y);
        }
    }

    printf("Minimum Spanning Tree (Kruskal):\n");
    for (int i = 0; i < V - 1; ++i) {
        printf("%d - %d\n", result[i].src, result[i].dest);
    }

    free(subsets);
}

// ฟังก์ชันทดสอบ
int main() {
    int V = 4;
    int E = 5;

    struct Graph* graph = createGraph(V, E);

    graph->edges[0].src = 0;
    graph->edges[0].dest = 1;
    graph->edges[0].weight = 10;

    graph->edges[1].src = 0;
    graph->edges[1].dest = 2;
    graph->edges[1].weight = 6;

    graph->edges[2].src = 0;
    graph->edges[2].dest = 3;
    graph->edges[2].weight = 5;

    graph->edges[3].src = 1;
    graph->edges[3].dest = 3;
    graph->edges[3].weight = 15;

    graph->edges[4].src = 2;
    graph->edges[4].dest = 3;
    graph->edges[4].weight = 4;

    primMST(graph);
    //kruskalMST(graph);

    free(graph->edges);
    free(graph);

    return 0;
}