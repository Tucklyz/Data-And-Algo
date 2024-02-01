#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 100 //กำหนดขนาดของอาเรย์

typedef struct Node { //สร้างโหนด
    char data[MAX];
    struct Node* next;
} Node;

Node* top = NULL; //กำหนดตัวแปร pointer top ให้ชี้ไปยังโหนดบนสุดของ 
                  //stack โดยกำหนดให้เป็น NULL เพื่อระบุว่า stack ว่าง

void push(char x[]) { //ฟังก์ชัน push สำหรับเพิ่มข้อมูลเข้าใน stack 
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = top;
    top = newNode;
    strcpy(newNode->data, x); 
}

char* pop() { //ฟังก์ชัน pop ใช้สำหรับนำข้อมูลออกจาก stack
    char* popped = (char*)malloc(MAX * sizeof(char));
    Node* temp;
    if (top == NULL) {
        return NULL;
    } else {
        temp = top;
        top = top->next;
        strcpy(popped, temp->data);
        free(temp);
        return popped;
    }
}

char* stacktop() { //ฟังก์ชัน stacktop ใช้สำหรับดึงข้อมูลที่อยู่บนสุดของ stack
    char* returnValue = (char*)malloc(MAX * sizeof(char));
    if (top == NULL) {
        return NULL;
    } else {
        strcpy(returnValue, top->data);
        return returnValue;
    }
}

void printStack() { //ฟังก์ชัน printStack ใช้สำหรับพิมพ์ข้อมูลทั้งหมดใน stack ในกรณีที่ข้อมูลเป็นตัวอักษร
    Node* current = top;
    char dataStack[MAX][MAX];
    int index = 0;
    while (current != NULL) {
        strcpy(dataStack[index], current->data);
        current = current->next;
        index++;
    }
    for (int i = index - 1; i >= 0; i--) {
        printf("%s", dataStack[i]);
    }
    printf("\n");
}

void printStackInt() { //ฟังก์ชัน printStack ใช้สำหรับพิมพ์ข้อมูลทั้งหมดใน stack ในกรณีที่ข้อมูลเป็นตัวเลข
    Node* current = top;
    char dataStack[MAX][MAX];
    int index = 0;
    while (current != NULL) {
        strcpy(dataStack[index], current->data);
        current = current->next;
        index++;
    }
    for (int i = index - 1; i >= 0; i--) {
        if (i == 0) {
            printf("%s", dataStack[i]);
        } else {
            printf("%s, ", dataStack[i]);
        }
    }
    printf("\n");
}

int isOperator(char ch) { //ฟังก์ชัน isOperator ใช้สำหรับตรวจสอบตัวดำเนินการทางคณิตศาสตร์
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}


void displayTablePostToIn(char ch[]) { //ฟังก์ชัน displayTablePostToIn ใช้เพื่อแสดงขั้นตอนการหาผลลัพธ์ของ postfix
    printf("========================================================\n");
    printf("%-1s%-8s%-13s%-15s\n", "", "Step", "Symbol", "Stack");
    printf("========================================================\n");
    char temp[2], op[2] = {'(', '\0'}, cl[2] = {')', '\0'};
    int i = 0, num;
    while (ch[i] != '\0') { //ทำงานจนกว่าข้อมูลในอาร์เรย์เท่ากับ '\0'
        char exp[MAX] = {'\0'}, op1[MAX] = {'\0'}, op2[MAX] = {'\0'};
        temp[0] = ch[i];
        temp[1] = '\0';
        if (isalpha(ch[0])) { //ตรวจสอบตัวอักษร
            if (isalpha(temp[0])) { //ตรวจสอบตัวอักษร
                push(temp);
            } else if (isOperator(temp[0])) { //ตรวจสอบตัวดำเนินการ
                strcpy(op2, pop());
                strcpy(op1, pop());
                strcat(exp, op);
                strcat(exp, op1);
                strcat(exp, temp);
                strcat(exp, op2);
                strcat(exp, cl);
                push(exp);
            } else { 
                printf("Invalid Arithmetic expression!\n");
                exit(0);
            }
            printf("%-2s%-9d%-11c", "", i + 1, ch[i]);
            printStack(); //แสดงข้อมูลใน stack
            i++;
        } else if (isdigit(ch[0])) { //ตรวจสอบตัวเลข
            if (isdigit(temp[0])) { //ตรวจสอบตัวเลข
                push(temp);
            } else if (isOperator(temp[0])) { //ตรวจสอบตัวดำเนินการ
                strcpy(op2, pop());
                strcpy(op1, pop());
                switch (temp[0]) {
                    case '+':
                        num = atoi(op1) + atoi(op2);
                        break;
                    case '-':
                        num = atoi(op1) - atoi(op2);
                        break;
                    case '*':
                        num = atoi(op1) * atoi(op2);
                        break;
                    case '/':
                        num = atoi(op1) / atoi(op2);
                        break;
                    case '^':
                        num = pow(atoi(op1), atoi(op2));
                        break;
                    default:
                        break;
                }
                sprintf(exp, "%d", num);
                push(exp);
            } else if (temp[0] == ' ') {
                continue;
            } else {
                printf("Invalid Arithmetic expression!\n");
                exit(0);
            }
            printf("%-2s%-9d%-11c", "", i + 1, ch[i]);
            printStackInt(); //แสดงข้อมูลใน stack
            i++;
        }
    }
    printf("========================================================\n");
    char* s = stacktop();
    if (s != NULL) { //แสดงผลลัพธ์
        printf("Result: %s\n", s);
    } else {
        printf("Result: \n");
    }
    printf("========================================================\n");
}

int main() {
	printf("        [ENG23 2031 Data Structures and Algorithm]\n\n");
    printf("            Welcome to our project [Group 7]\n\n");
    printf("   This project can help you convert Postfix To Result");
    printf("\n\n--------------------- Developers -----------------------");
    printf("\n\nB6508494 Kongsawan Chanthabouly");
	printf("\n\nB6509293 Parichat Sujarit");
	printf("\n\nB6514136 Rungnapha Khuanphon");
	printf("\n\nB6515652 Nadthapat Phuttaruksa");
    printf("\n\n---------------------- Present -------------------------");
    printf("\n\nDr. Supaporn Bunrit");
    printf("\n\n--------------------------------------------------------");
    printf("\n\n        [ Press Enter to continue ... ]");
    fflush(stdin);
    scanf("%*[^\n]");
    system("cls");
    getchar();

    printf("\n\n                     [ Start... ]");
    printf("\n\n********* PROGRAM POSTFIX TO RESULT CONVERTER ************\n\n");
    printf("Please Enter your Postfix \n\n");
    char postfix[MAX];
    printf("postfix: ");
    fgets(postfix, sizeof(postfix), stdin); //รับข้อมูลจากแป้นพิมพ์
    postfix[strcspn(postfix, "\n")] = '\0'; //หาตำแหน่งของ "\n" ในอาร์เรย์ และเปลี่ยนค่าเป็น '\0'
	displayTablePostToIn(postfix); //แสดงขั้นตอนการหาผลลัพธ์
	printf("\n                   [ Thank you... ]");
    printf("\n ");
    return 0;
}