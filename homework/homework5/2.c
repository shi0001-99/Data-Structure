#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main() {
    int n;  
    scanf_s("%d", &n);

    char arr[35];
    scanf_s("%s", arr, 35);


    char* stack = (char*)malloc(sizeof(char) * (n+ 1));
    int top = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] == '(') {
            stack[top++] = 0;
        }
        else {
            int val = stack[--top];
            if (val == 0) {
                val = 1;
            }
            else {
                val *= 2;
            }
            if (top == 0) {
                stack[top++] = val;
            }
            else {
                stack[top - 1] += val;
            }
        }
    }
    printf("%d", stack[0]);
    return 0;
}