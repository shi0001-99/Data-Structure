#include<stdio.h>

typedef struct{
    ElemType *data;
    int front;
    int rear;
}Queue;

Queue *initQueue(){
    Queue *q=(Queue *)malloc(sizeof(Queue));
    q->data=(ElemType*)malloc(sizeof(ElemType)*MAXSIZE);
    q->front=0;
    q->rear=0;
    return q;
}
int main(){
    return 0;
}

//-------------------------------------
typedef struct{
    int front;//队列头索引
    int rear;//队列尾索引
    Elmt *base;//存储空间基地址
    int size;//存储空间容量
}Queue;

