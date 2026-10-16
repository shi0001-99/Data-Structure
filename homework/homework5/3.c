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
    int top = 0;//栈里面的位置下表

    for (int i = 1; i <= n; i++) {
        stack[top++] = i;//进栈顺序12345
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
//------------------------------------------
int arr[1000005];
int stack[1000005];
int main(){
    int n;
    scanf_s("%d",&n);
    for(int i=0;i<n;i++){
        scanf_s("%d",&arr[i]);
    }
    int pos=0;
    int top=0;
    for(int i=1;i<=n;i++){
        stack[top++]=i;
        while(top>0 && stack[top-1]==arr[pos]){
            pos++;
            top--;
        }
    }
    if(top==0){
        printf("True");
    }
    else{
        printf("False");
    }
    return 0;
}

//------------------------------------------
int arr[1000005];
int stack[1000005];
int main(){
    int n;
    scanf_s("%d",&n);
    int top=0;
    int pos=0;
    for(int i=0;i<n;i++){
        scanf_s("%d",&arr[i]);
    }
    for(int i=1;i<=n;i++){
        stack[top++]=i;
        while(top>0 && stack[top-1]==arr[pos]){
            pos++;
            top--;
        }
    }
    if(top==0){
        printf("True");
    }
    else{
        printf("False");
    }
    return 0;
}