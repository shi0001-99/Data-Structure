中秋节快到了，小蓝鲸打算亲手做一个月饼送给大蓝鲸。他最近迷上了回文数，因此打算让月饼的重量𝑆是一个十进制下的回文数。
大蓝鲸是一个程序员，习惯使用二进制，因此小蓝鲸希望 𝑆的二进制表示也是一个回文数，这样的月饼才是“好月饼”。
小蓝鲸的厨房中只有重量为𝑊的食材，他需要补充一些来制作“好月饼”，但是他不知道应该补充食材到多少重量，你可以帮帮他吗？
请输出月饼重量（补充后食材重量）为多少。 S是所有满足条件且大于 W 的数中的最小值

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

bool istenhuiwen(int n){
    char num[20];
    int index=0;
    int temp=n;
    while(temp>0){
        num[index++]=temp%10+'0';
        temp/=10;
    }
    for(int i=0;i<index/2;i++){
        if(num[i]!=num[index-1-i]){
            return false;
        }
    }
    return true;
}

bool istwohuiwen(int n){
    char num[64];
    int index=0;
    int temp=n;
    while(temp>0){
        num[index++]=(temp%2)? '1': '0';
        temp/=2;
    }
    for(int i=0;i<index/2;i++){
        if(num[i]!=num[index-1-i]){
            return false;
        }
    }
    return true;
}

int main(){
    int W;
    scanf("%d",&W);
    int S=W+1;
    while(true){
        if(istenhuiwen(S) && istwohuiwen(S)){
            printf("%d",S);
            break;
        }
        S++;
    }
    return 0;
}