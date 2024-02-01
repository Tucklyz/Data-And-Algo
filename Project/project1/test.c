#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX 100

typedef struct {
    char stack[MAX];
} Stack;

Stack s[MAX];
int top = -1;

void displayTablePostToIn(char[]);
int isFull();
int isEmpty();
void push(char*);
int isOperator(char);
char* pop();

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
    fgets(postfix, sizeof(postfix), stdin);
    postfix[strcspn(postfix, "\n")] = '\0';
	displayTablePostToIn(postfix);
	printf("\n                   [ Thank you... ]");
    printf("\n ");
    return 0;
}

void displayTablePostToIn(char ch[]){
	printf("========================================================\n");
    printf("%-1s%-8s%-13s%-15s\n", "", "Step", "Symbol", "Stack");
    printf("========================================================\n");
	char temp[2], op[2] = {'(', '\0'}, cl[2] = {')', '\0'}, st[MAX] = {'\0'} ;
	int i = 0, nop = 0, num;
	while (ch[i] != '\0') {
        char exp[MAX] = {'\0'}, op1[MAX] = {'\0'}, op2[MAX] = {'\0'};
        temp[0] = ch[i];
        temp[1] = '\0';
		if(isalpha(ch[0])){
			if (isalpha(temp[0])) {
				push(temp);
				nop++;
			} else if (isOperator(temp[0])) {
				strcpy(op2, pop());
				strcpy(op1, pop());
				strcat(exp, op);
				strcat(exp, op1);
				strcat(exp, temp);
				strcat(exp, op2);
				strcat(exp, cl);
				push(exp);
				nop--;
			} else {
				printf("Invalid Arithmetic expression!\n");
				exit(0);
			}
			for(int j = 0 ; j < nop ; j++){
				if(j == 0){
					strcpy(st,s[j].stack);
				}else{
					strcat(st,s[j].stack);
				}
			}
			printf("%-2s%-9d%-11c%-15s\n", "", i + 1, ch[i], st);
			i++;
		}else if(isdigit(ch[0])){
			if (isdigit(temp[0])) {
				push(temp);
				nop++;
			} else if (isOperator(temp[0])) {
				strcpy(op2, pop());
				strcpy(op1, pop());
				switch (temp[0]){
					case '+': num = atoi(op1) + atoi(op2); break;
					case '-': num = atoi(op1) - atoi(op2); break;
					case '*': num = atoi(op1) * atoi(op2); break;
					case '/': num = atoi(op1) / atoi(op2); break;
					case '^': num = pow(atoi(op1),atoi(op2)); break;
					default: break;
				}
				sprintf(exp, "%d", num);
				push(exp);
				nop--;
			} else if(temp[0] == ' '){
				continue;
			}else {
				printf("Invalid Arithmetic expression!\n");
				exit(0);
			}
			for(int j = 0 ; j < nop ; j++){
				if(j == 0){
					strcpy(st,s[j].stack);
				}else{
					strcat(st,", ");
					strcat(st,s[j].stack);
				}
			}
			printf("%-2s%-9d%-11c%-15s\n", "", i + 1, ch[i], st);
			i++;
		}
	}
    printf("========================================================\n");
    printf("Postfix: %s\n", st);
    printf("========================================================\n");
}

void push(char* item) {
    if (isFull()) {
        printf("Overflow detected!\n");
    } else {
        strcpy(s[++top].stack, item);
    }
}

int isFull() {
    return top == MAX - 1;
}

int isEmpty() {
    return top == -1;
}

int isOperator(char sym) {
    return (sym == '+' || sym == '-' || sym == '*' || sym == '/' || sym == '^');
}

char* pop() {
    if (isEmpty()) {
        exit(0);
    }
    return s[top--].stack;
}