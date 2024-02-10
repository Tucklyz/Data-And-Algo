#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define INF 9999999

typedef struct edge {
    int u, v, w;
} edge;

typedef struct edge_list {
    edge *data;
    int n;
} edge_list;

edge_list elist;

void kruskalAlgo(int V, int Graph[V][V]);
int find(int belongs[], int vertexno);
void applyUnion(int belongs[], int c1, int c2, int V);
void sort();
void primAlgo(int V, int Graph[V][V]);

int main() {
    int V;
    printf("Please enter the number of vertices: ");
    scanf("%d", &V);

    int Graph[V][V];
    for (int i = 0; i < V; i++) {
        Graph[i][i] = 0;
        for (int j = i+1; j < V; j++) {
            printf("Weight of Edge (%c) - (%c) = ", i+'A', j+'A');
            scanf("%d", &Graph[i][j]);
            Graph[j][i] = Graph[i][j];

        }
    }
    system("cls");
    printf("Kruskal's Algorithm:\n");
    kruskalAlgo(V, Graph);

    printf("\nPrim's Algorithm:\n");
    primAlgo(V, Graph);

    return 0;
}

void kruskalAlgo(int V, int Graph[V][V]) {
    int belongs[V], i, j, cno1, cno2;
    elist.n = 0;
    elist.data = malloc(V * V * sizeof(edge)); 

    for (i = 1; i < V; i++)
        for (j = 0; j < i; j++) {
            if (Graph[i][j] != 0) {
                elist.data[elist.n].u = i;
                elist.data[elist.n].v = j;
                elist.data[elist.n].w = Graph[i][j];
                elist.n++;
            }
        }

    sort();

    for (i = 0; i < V; i++)
        belongs[i] = i;

    printf("Edge : Weight\n");

    for (i = 0; i < elist.n; i++) {
        cno1 = find(belongs, elist.data[i].u);
        cno2 = find(belongs, elist.data[i].v);

        if (cno1 != cno2) {
            printf("%c - %c : %d\n", elist.data[i].u+'A', elist.data[i].v+'A', elist.data[i].w);
            applyUnion(belongs, cno1, cno2, V);
        }
    }

    free(elist.data); 
}

int find(int belongs[], int vertexno) {
    return (belongs[vertexno]);
}

void applyUnion(int belongs[], int c1, int c2, int V) {
    int i;

    for (i = 0; i < V; i++)
        if (belongs[i] == c2)
            belongs[i] = c1;
}

void sort() {
    int i, j;
    edge temp;

    for (i = 1; i < elist.n; i++)
        for (j = 0; j < elist.n - 1; j++)
            if (elist.data[j].w > elist.data[j + 1].w) {
                temp = elist.data[j];
                elist.data[j] = elist.data[j + 1];
                elist.data[j + 1] = temp;
            }
}

void primAlgo(int V, int Graph[V][V]) {
    int no_edge;
    int selected[V];
    memset(selected, false, sizeof(selected));
    no_edge = 0;
    selected[0] = true;
    int x, y;
    printf("Edge : Weight\n");

    while (no_edge < V - 1) {
        int min = INF;
        x = 0;
        y = 0;
        for (int i = 0; i < V; i++) {
            if (selected[i]) {
                for (int j = 0; j < V; j++) {
                    if (!selected[j] && Graph[i][j]) {
                        if (min > Graph[i][j]) {
                            min = Graph[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        printf("%c - %c : %d\n", x+'A', y+'A', Graph[x][y]);
        selected[y] = true;
        no_edge++;
    }
}
