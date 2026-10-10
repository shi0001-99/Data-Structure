//小蓝鲸照镜子
#include<stdio.h>
#include<stdlib.h>
char arr[1000005];
void reverse(char *arr,int a,int b){
    
    while(a<b){
        char temp=arr[a];
        arr[a]=arr[b];
        arr[b]=temp;
        a++;
        b--;
    }
}
int main(){
    int n,m,q;
    scanf("%d%d%d",&n,&m,&q);
    
    for(int i=1;i<=n;i++){
        scanf(" %c",&arr[i]);
    }
    int op,pos;
    
    for(int i=0;i<q;i++){
        scanf("%d%d",&op,&pos);
        if(op==1){
            reverse(arr,pos,pos+m-1);
        }
        else{
            printf("%c",arr[pos]);
        }
    }
}