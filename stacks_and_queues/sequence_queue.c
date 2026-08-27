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