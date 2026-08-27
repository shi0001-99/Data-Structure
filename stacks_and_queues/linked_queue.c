#include<stdio.h>

typedef struct QueneNode{
    ElemType data;
    struct QueueNode *next;
}QueueNode;

typedef struct{
    QueueNode *front;
    QueueNode *rear;
}Queue;

Queue *initQueue(){
    Queue *q=(Queue *)malloc(sizeof(Queue));
    QueueNode* node=(QueueNode*)malloc(sizeof(QueueNode));
    node->next=NULL;
    q->front=node;
    q->rear=node;
    return q;
}

void equeue(Queue *q,ElemType e){
    QueueNode *node=(QueueNode*)malloc(sizeof(QueueNode));
    node->data=e;
    node->next=NULL;
    q->rear->next=node;
    q->rear=node;
}

int dqueue(Queue *q,ElemType *e){
    QueueNode *node=q->front->next;
    *e=node->data;//把出队的元素保存下来
    q->front->next=node->next;
    if(q->rear==node){
        q->rear=q->front;
    }
    free(node);
    return 1;
}

int main(){
    return 0;
}