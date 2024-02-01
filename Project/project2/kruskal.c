#include <stdio.h>
#include <stdlib.h>

#define V 7 // จำนวน vertices ในกราฟ

// โครงสร้างข้อมูลแบบ Edge ในกราฟ
typedef struct {
    int src, dest, weight;
} Edge;

// โครงสร้างข้อมูลแบบ Subset ในการใช้ Union-Find
typedef struct {
    int parent, rank;
} Subset;

// ฟังก์ชันเปรียบเทียบ Edge ตามน้ำหนัก
int compareEdges(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// ฟังก์ชันในการหา root ของ subset ที่ i
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

// ฟังก์ชันในการรวม subset ที่มี root ต่างกัน
void Union(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootX].parent = rootY;
        subsets[rootY].rank++;
    }
}

// ฟังก์ชันในการหา MST ด้วย Kruskal's Algorithm
void kruskalMST(Edge graph[], int e) {
    qsort(graph, e, sizeof(Edge), compareEdges);  // เรียงลำดับ Edge ตามน้ำหนัก

    Edge result[V]; // เก็บผลลัพธ์ที่เป็น MST
    int resultIndex = 0; // Index สำหรับ result[]

    Subset* subsets = (Subset*)malloc(V * sizeof(Subset));  // สร้าง subset สำหรับ Union-Find

    // กำหนดค่าเริ่มต้นให้กับ subset แต่ละตัว
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    int i = 0; // Index สำหรับ sorted edges
    while (resultIndex < V - 1 && i < e) {
        Edge nextEdge = graph[i++];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        if (x != y) {
            result[resultIndex++] = nextEdge;
            Union(subsets, x, y);
        }
    }

    // แสดงผลลัพธ์
    printf("Edge \tWeight\n");
    for (int j = 0; j < resultIndex; j++)
        printf("%d - %d \t%d \n", result[j].src, result[j].dest, result[j].weight);

    free(subsets);
}

int main() {
    // ตัวอย่างกราฟที่แทนด้วย Edge
    Edge graph[] = {
        {0, 1, 3},
        {0, 6, 2},
        {1, 6, 1},
        {1, 2, 6},
        {2, 6, 8},
        {2, 5, 4},
        {5, 6, 5},
        {2, 3, 2},
        {3, 4, 7},
        {2, 4, 9},
        {4, 5, 8},
    };

    int edges = sizeof(graph) / sizeof(graph[0]);

    kruskalMST(graph, edges);

    return 0;
}





// **อธิบาย:**
// 1. `compareEdges`: ฟังก์ชันนี้ใช้เพื่อเปรียบเทียบ Edge ตามน้ำหนักของมัน.
// 2. `find`: ฟังก์ชันนี้ใช้ในการหา root ของ subset ที่ i โดยใช้เทคนิค Path Compression.
// 3. `Union`: ฟังก์ชันนี้ใช้ในการรวม subset ที่มี root ต่างกันโดยใช้เทคนิค Union by Rank.
// 4. `kruskalMST
// `: ฟังก์ชันหลักในการคำนวณ MST ด้วย Kruskal's Algorithm.
//    - เรียงลำดับ Edge ตามน้ำหนัก.
//    - สร้าง subset และกำหนดค่าเริ่มต้นให้.
//    - ทำการเลือก Edge ที่มีน้ำหนักน้อยที่สุดในแต่ละขั้นตอนและตรวจสอบว่าเป็นส่วนของ MST หรือไม่.
//    - ถ้าไม่เป็นส่วนของ MST ก็ทำการรวม subset.
//    - ทำขั้นตอนนี้จนกระทั่ง MST ถูกสร้างขึ้น.
//    - แสดงผลลัพธ์ MST ที่ได้.
// 5. `main`: สร้างตัวแปร `graph` และเรียกใช้ `kruskalMST` เพื่อคำนวณและแสดงผล MST ที่ได้.

// 1. **compareEdges(const void* a, const void* b):**
//    - **คำอธิบาย:** ฟังก์ชันเปรียบเทียบ Edge ตามน้ำหนักในการใช้ในการเรียงลำดับ Edge ในการคำนวณ Kruskal's Algorithm.
//    - **พารามิเตอร์:**
//      - `const void* a`, `const void* b`: Pointer ไปยังข้อมูลของ Edge a และ b ที่จะเปรียบเทียบ.
//    - **คืนค่า:**
//      - ค่าน้อยกว่า 0 ถ้าน้ำหนักของ Edge a น้อยกว่า Edge b.
//      - ค่าเท่ากับ 0 ถ้าน้ำหนักของ Edge a เท่ากับ Edge b.
//      - ค่ามากกว่า 0 ถ้าน้ำหนักของ Edge a มากกว่า Edge b.

// 2. **find(Subset subsets[], int i):**
//    - **คำอธิบาย:** ฟังก์ชันในการหา root ของ subset ที่ i โดยใช้ Union-Find.
//    - **พารามิเตอร์:**
//      - `Subset subsets[]`: ตาราง subset ที่ใช้ใน Union-Find.
//      - `int i`: Index ของ subset ที่ต้องการหา root.
//    - **คืนค่า:**
//      - ค่า root ของ subset ที่ i.

// 3. **Union(Subset subsets[], int x, int y):**
//    - **คำอธิบาย:** ฟังก์ชันในการรวม subset ที่มี root ต่างกัน.
//    - **พารามิเตอร์:**
//      - `Subset subsets[]`: ตาราง subset ที่ใช้ใน Union-Find.
//      - `int x`, `int y`: ลำดับของ subset ที่ต้องการรวม.
//    - **การทำงาน:**
//      - หา root ของ subset ที่ x และ y.
//      - ถ้า subset ที่ x มี rank น้อยกว่า subset ที่ y ให้กำหนด parent ของ x เป็น y.
//      - ถ้า subset ที่ x มี rank มากกว่า subset ที่ y ให้กำหนด parent ของ y เป็น x.
//      - ถ้า subset ที่ x และ y มี rank เท่ากันให้เลือกใดก็ได้ และเพิ่ม rank ขึ้น.

// 4. **kruskalMST(Edge graph[], int e):**
//    - **คำอธิบาย:** ฟังก์ชันหลักในการคำนวณ MST ด้วย Kruskal's Algorithm.
//    - **พารามิเตอร์:**
//      - `Edge graph[]`: ตารางแสดงข้อมูลของ Edge ในกราฟ.
//      - `int e`: จำนวนของ Edge ในกราฟ.
//    - **การทำงาน:**
//      - เรียงลำดับ Edge ตามน้ำหนัก.
//      - สร้าง subset สำหรับ Union-Find.
//      - วนลูปเพื่อสร้าง MST โดยเลือก Edge ที่น้ำหนักน้อยที่สุด.
//      - แสดงผลลัพธ์ MST.