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

int equeue(Queue *Q,ElemType e){
    if((Q->rear+1)%MAXSIZE==Q->front){
        printf("满了\n");
        return 0;
    }
    Q->data[Q->rear]=e;
    Q->rear=(Q->rear+1)%MAXSIZE;
    return 1;
}

int main(){
    return 0;
}