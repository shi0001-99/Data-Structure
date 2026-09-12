新的一个学期到了，小蓝鲸们也开启了新的生活。在某一次主题团日活动中，需要抽取同学接受惩罚进行表演。 班长想出了这样一个方法，让大家在抽取一个同学的过程中还可以进行互动，该抽取方法是：
班级里共有n位小蓝鲸，每个人都拥有自己的编号 1~n 。 小蓝鲸们按照编号顺序坐成一圈。班长先抽取一个数字 m， 然后从 1 号小蓝鲸起从1开始数数， 数到 m的小蓝鲸起立并往后退， 且该小蓝鲸起立后退后，从下一个小蓝鲸重新开始从1数数，每次数到m的小蓝鲸起立后退。 一直重复数数到最后只剩下一个人。
请输出每次起立并后退的小蓝鲸的编号，并输出游戏结束时剩下的最后一位需要接受惩罚的小蓝鲸的编号。
输入格式
输入两个整数 n,m
输出格式
共输出两行。
第一行输出 n-1 个整数，按顺序输出每个出圈人的编号。
第二行输出最后剩下的人的编号。

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Node{
    int data;
    struct Node* next;
}Node;

typedef struct List{
    Node* head;
    Node* tail;
}List;


List initialize(int n){
    Node* head=(Node*)malloc(sizeof(Node));
    head->data=1;
    Node* curr=head;
    for(int i=2;i<=n;i++){
        Node* temp=(Node*)malloc(sizeof(Node));
        temp->data=i;
        curr->next=temp;
        curr=temp;
    }
    List list;
    list.head=head;
    list.tail=curr;
    tail->next=head;
    return list;
}

void josephus(List*list,int n,int m){
    Node*curr=list->head;
    Node*prev=list->tail;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<m-1;j++){
            prev=curr;
            curr=curr->next;
        }
        printf("delete %d\n",curr->data);
        prev->next=curr->next;
        free(curr);
        curr=prev->next;
    }
}


int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    List list;
    list=initialize(n);
    josephus(&list,n,m);
    return 0;
}