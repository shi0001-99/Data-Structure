#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d",&n);
    int a[100000];
    int b[100000];
    int cha[100000];
    int exist[100000];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<n;i++){
        scanf("%d",&b[i]);
    }
    for(int i=0;i<n;i++){
        cha[i]=(a[i]>b[i])?(a[i]-b[i]):(b[i]-a[i]);
    }
    for(int i=0;i<n;i++){
        exist[i]=1;
    }
    int as=0;
    int bs=0;
    for()
}
    