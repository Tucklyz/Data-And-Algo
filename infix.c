#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

Node* top = NULL;

void push(char x) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = top;
    top = newNode;
    newNode->data = x;
}

char pop() {
    char popped;
    Node* temp;
    if (top == NULL) {
        return '\0';
    } else {
        temp = top;
        top = top->next;
        popped = temp->data;
        free(temp);
        return popped;
    }
}

char stacktop() {
    if (top == NULL) {
        return '\0';
    } else {
        return top->data;
    }
}

int checkPriority(char temp) {
    int priority;
    if (temp == '(') {
        priority = 0;
    } else if (temp == '^') {
        priority = 3;
    } else if (temp == '*' || temp == '/') {
        priority = 2;
    } else {
        priority = 1;
    }
    return priority;
}

void displayTableInToPost(char ch[], int size) {
    printf("========================================================\n");
    printf("%-1s%-8s%-13s%-15s%-20s\n", "", "Step", "Symbol", "Stack", "Output");
    printf("========================================================\n");
    char st[size], out[size];
    for (int i = 0; i <= size; i++) {
        st[i] = '\0';
        out[i] = '\0';
    }
    int i, nst = 0, nout = 0;
    for (i = 0; i < size; i++) {
        if (ch[i] == '(') {
            push(ch[i]);
            st[nst++] = ch[i];
            printf("%-2s%-9d%-11c%-15s%-18s\n", "", i + 1, ch[i], st, out);
        } else if (ch[i] == ')') {
            while (stacktop() != '(') {
                out[nout++] = pop();
                st[nst--] = '\0';
            }
            pop();
            st[nst--] = '\0';
            st[nst] = '\0';
            printf("%-2s%-9d%-11c%-15s%-18s\n", "", i + 1, ch[i], st, out);
        } else if (isdigit(ch[i]) || isalpha(ch[i])) {
            out[nout++] = ch[i];
            printf("%-2s%-9d%-11c%-15s%-18s\n", "", i + 1, ch[i], st, out);
        } else {
            if (stacktop() == '\0' || stacktop() == '(') {
                push(ch[i]);
                st[nst++] = ch[i];
                printf("%-2s%-9d%-11c%-15s%-18s\n", "", i + 1, ch[i], st, out);
            } else {
                if (checkPriority(ch[i]) <= checkPriority(stacktop())) {
                    while ((checkPriority(ch[i]) <= checkPriority(stacktop())) && (stacktop() != '\0')) {
                        st[nst--] = '\0';
                        out[nout++] = pop();
                    }
                }
                push(ch[i]);
                st[nst++] = ch[i];
                printf("%-2s%-9d%-11c%-15s%-18s\n", "", i + 1, ch[i], st, out);
            }
        }
    }
    int check = 0;
    while (stacktop() != '\0') {
        out[nout++] = pop();
        check++;
    }
    if (check > 0) {
        printf("%-2s%-9d%-11s%-15s%-18s\n", "", i + 1, "", "", out);
    }
    printf("========================================================\n");
    printf("Postfix: %s\n", out);
    printf("========================================================\n");
}

int main() {
    printf("        [ENG23 2031 Data Structures and Algorithm]\n\n");
    printf("            Welcome to our project [Group 7]\n\n");
    printf("   This project can help you convert Infix to Postfix ");
    printf("\n\n--------------------- Developers -----------------------");
    printf("\n\nB6508494 Kongsawan Chanthabouly\n\nB6509293 Parichat Sujarit\n\nB6514136 Rungnapha Khuanphon\n\nB6515652 Nadthapat Phuttaruksa");
    printf("\n\n---------------------- Present -------------------------");
    printf("\n\nDr. Supaporn Bunrit");
    printf("\n\n--------------------------------------------------------");
    printf("\n\n        [ Press Enter to continue ... ]");
    fflush(stdin);
    scanf("%*[^\n]");
    system("cls");
    getchar();

    printf("\n\n                     [ Start... ]");
    printf("\n\n********* PROGRAM INFIX TO POSTFIX CONVERTER ************\n\n");
    printf("Please Enter your Infix \n\n");
    char c;
    int size = 0;
    printf("Infix: ");
    do{
    scanf("%c",&c);
        if(c != '\n'){
            size++;
            push(c);
        }
    } while (c != '\n');
    char ch[size];
    for (int i = size - 1; i >= 0; i--) {
        ch[i] = pop();
    }
    displayTableInToPost(ch, size);
    printf("\n                   [ Thank you... ]");
    printf("\n ");
    return 0;
}

