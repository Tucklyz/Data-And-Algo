#include <stdio.h>
#include <limits.h>

#define V 7 // จำนวนของ vertices ในกราฟ

// ฟังก์ชันหาคีย์ที่น้อยที่สุดจาก key[] และเป็นส่วนของ MST
int minKey(int key[], int mstSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

// ฟังก์ชันแสดงผลของ MST
void printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

// ฟังก์ชันหลักในการคำนวณ MST ด้วยวิธี Prim's Algorithm
void primMST(int graph[V][V]) {
    int parent[V]; // บอกว่า vertex ใน index นี้ถูกเชื่อมกับ vertex ไหน
    int key[V];    // เก็บค่า key ที่ใช้เพื่อหา minimum weight edge
    int mstSet[V]; // เก็บข้อมูลว่า vertex นี้เป็นส่วนของ MST แล้วหรือไม่

    // กำหนดค่าเริ่มต้นของ key เป็น INFINITE และ mstSet เป็น 0
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    // เริ่มต้น MST ด้วย vertex แรก
    key[0] = 0;     // ทำให้ key เป็น 0 เพื่อให้ vertex นี้ถูกเลือกเป็น vertex แรก
    parent[0] = -1; // vertex แรกเป็น root ของ MST

    // MST จะมี V vertices
    for (int count = 0; count < V - 1; count++) {
        // เลือก vertex ที่มี key น้อยที่สุดจากที่ยังไม่เข้า MST
        int u = minKey(key, mstSet);

        // ทำเครื่องหมายว่า vertex นี้เป็นส่วนของ MST แล้ว
        mstSet[u] = 1;

        // อัปเดต key และ parent ของ vertices ที่เชื่อมโยงกับ vertex ที่เพิ่งเลือก
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // แสดงผลลัพธ์ MST
    printMST(parent, graph);
}

int main() {
    // ตัวอย่างกราฟที่แทนด้วย adjacency matrix
    int graph[V][V] = {
        {0, 3, 0, 0, 0, 0, 2},
        {3, 0, 6, 0, 0, 0, 1},
        {0, 6, 0, 2, 9, 4, 8},
        {0, 0, 2, 8, 0, 0, 0},
        {0, 0, 9, 8, 0, 8, 0},
        {0, 0, 4, 0, 7, 0, 5},
        {2, 1, 7, 0, 0, 5, 0}
    };

    // เรียกใช้ฟังก์ชันคำนวณ MST ด้วย Prim's Algorithm
    primMST(graph);

    return 0;
}


// **อธิบาย:**
// 1. `minKey`: หาคีย์ที่น้อยที่สุดจากคีย์ที่ยังไม่ได้รวมเข้าใน MST.
// 2. `printMST`: แสดงผลลัพธ์ของ MST ที่ได้.
// 3. `primMST`: ฟังก์ชันหลักในการคำนวณ MST ด้วยวิธี Prim's Algorithm.
//    - สร้างตัวแปร `parent`, `key`, และ `mstSet` เพื่อเก็บข้อมูลที่ใช้ในการคำนวณ.
//    - ทำการกำหนดค่าเริ่มต้นของ `key` เป็น `INT_MAX` และ `mstSet` เป็น 0.
//    - เริ่ม MST ด้วย vertex แรก (vertex 0).
//    - ในแต่ละขั้นตอน, เลือก vertex ที่มี key น้อยที่สุดจากที่ยังไม่ได้รวมเข้า MST.
//    - ทำเครื่องหมายว่า vertex นี้เป็นส่วนของ MST.
//    - อัปเดต key และ parent ของ vertices ที่เชื่อมโยงกับ vertex ที่เพิ่งเลือก.
//    - ทำขั้นตอนนี้จนกระทั่ง MST ถูกสร้างขึ้น.
// 4. `main`: สร้างตัวแปร `graph` เพื่อแทนกราฟในรูปแบบของ adjacency matrix และเรียกใช้ `primMST` เพื่อคำนวณและแสดงผล MST ที่ได้.

// 1. **minKey(int key[], int mstSet[]):**
//    - **คำอธิบาย:** หาคีย์ที่น้อยที่สุดจาก key[] ที่ยังไม่ได้รวมเข้าใน MST.
//    - **พารามิเตอร์:**
//      - `key[]`: ตารางเก็บคีย์ที่ใช้ในการหาคีย์ที่น้อยที่สุด.
//      - `mstSet[]`: ตารางเก็บข้อมูลว่า vertex นั้นๆ เป็นส่วนของ MST แล้วหรือไม่.
//    - **คืนค่า:**
//      - ดัชนีของ vertex ที่มีคีย์ที่น้อยที่สุดและยังไม่ได้รวมเข้าใน MST.

// 2. **printMST(int parent[], int graph[V][V]):**
//    - **คำอธิบาย:** แสดงผลของ MST ที่ถูกสร้าง.
//    - **พารามิเตอร์:**
//      - `parent[]`: ตารางเก็บข้อมูล parent ของแต่ละ vertex ใน MST.
//      - `graph[V][V]`: แมทริกซ์แสดงน้ำหนักของเส้นทางระหว่าง vertices.
//    - **การทำงาน:**
//      - แสดงข้อมูลของเส้นทางและน้ำหนักของ MST.

// 3. **primMST(int graph[V][V]):**
//    - **คำอธิบาย:** ฟังก์ชันหลักในการคำนวณ MST ด้วยวิธี Prim's Algorithm.
//    - **พารามิเตอร์:**
//      - `graph[V][V]`: แมทริกซ์แสดงน้ำหนักของเส้นทางระหว่าง vertices.
//    - **การทำงาน:**
//      - กำหนดค่าเริ่มต้นให้กับ key[], parent[], และ mstSet[].
//      - เลือก vertex แรกเป็นต้นแบบ.
//      - วนลูปเพื่อสร้าง MST ที่มีจำนวน vertices เท่ากับ V.
//      - สร้าง MST โดยเลือก edge ที่มีค่าน้อยที่สุดจาก vertex ที่อยู่นอก MST ไปยัง vertex ที่อยู่ใน MST.
//      - แสดงผล MST ที่ได้.

// 4. **main():**
//    - **คำอธิบาย:** ฟังก์ชันหลักที่ใช้เรียกใช้ Prim's Algorithm เพื่อหา Minimum Spanning Tree (MST).
//    - **การทำงาน:**
//      - สร้างแมทริกซ์แสดงน้ำหนักของเส้นทางระหว่าง vertices.
//      - เรียกใช้ฟังก์ชัน primMST() เพื่อคำนวณ MST และแสดงผลลัพธ์.