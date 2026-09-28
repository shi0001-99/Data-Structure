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

//队空 Q->front==Q->rear;
//指针循环 Q->rear=(Q->rear+1)%Q->size;
//队列容量=存储空间容量-1
//队满 Q->front==(Q->rear+1)%Q->size;
//队列目前长度 (Q->rear-Q->front+Q->size)%Q->size

void initQueue(Queue *Q){
    Q->base=(double*)calloc(6,sizeof(double));
    Q->front=Q->rear=0;
    Q->size=6;
}

int DeQ(Queue *Q,double *E){
    if(Q->front==Q->rear){
        return 1;
    }
    *E=Q->front;
    Q->front=(Q->front+1)%Q->size;
    return 0;
}

int Enq(Queue *Q,double e){
    if ((Q->rear + 1) % Q->size == Q->front) {
        return 1; //Err
    }
    Q->base[Q->rear] = e;
    Q->rear = (Q->rear + 1) % Q->size;
    return 0;
}