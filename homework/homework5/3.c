#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int arr[1000005];
int stack[1000005];
int main() {
    int n;  
    scanf_s("%d", &n);

    
    for (int i = 0; i < n; i++) {
        scanf_s("%d", &arr[i]);
    }
    int pos = 0;

    
    int top = 0;

    for (int i = 1; i <= n; i++) {
        stack[top++] = i;
        while (top>0 && stack[top-1] == arr[pos]) {
            pos++;
            top--;
        }
    }
    if (top == 0) {
        printf("True");
    }
    else {
        printf("False");
    }
    return 0;
}