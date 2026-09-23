#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main() {
    char arr[100005];
    scanf_s("%s", arr,100005);
    int k;  
    scanf_s("%d", &k);

    int length = strlen(arr);
    char* stack = (char*)malloc(sizeof(char) * (length + 1));
    int top = 0;

    for (int i = 0; i < length; i++) {
        char digit = arr[i];
        while (k > 0 && top > 0 && stack[top - 1] > digit) {
            top--;
            k--;
        }
        stack[top++] = digit;
    }
    if (k > 0) {
        top -= k;
    }
    int start = 0;
    while (start<top && stack[start] == '0') {
        start++;
    }
    if (start == top) {
        printf("0");
    }
    else {
        while (start < top) {
            printf("%c", stack[start]);
            start++;
        }
    }
    return 0;
}