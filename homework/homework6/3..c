//小蓝鲸的和谐队伍
#include<stdlib.h>
#include<stdio.h>
int arr[1000005];
int main(){
    int n,limit;
    scanf("%d%d",&n,&limit);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    int length=1;
    int max=-1;
    for(int i=1;i<n;i++){
        if((arr[i]-arr[i-1]<=limit&&arr[i-1]-arr[i]<=limit)  || (arr[i-1]-arr[i]<=limit && arr[i]-arr[i-1]<=limit)){
            length++;
        }
        else{
            length=1;
        }
        max=(length>max)?length:max;
    }
    printf("%d",max);
    return 0;
}