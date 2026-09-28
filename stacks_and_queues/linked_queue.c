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



//------------------------------------------------------
typedef struct{
    Elmt data;
    struct Node *next;
}next;

typedef struct{
    Node *front;
    Node *rear;
    int size;//队列的当前长度
}Queue;

void initqueue(Queue* Q){
    Q->front =NULL;
    Q->rear =NULL;
    Q->size=0;
}

int EnQ(Queue *Q,double e){
    Node *N=(Node*)malloc(sizeof(Node));
    N->data=e;
    N->next=NULL;
    if(!Q->front){
        Q->front=Q->rear=N;
    }
    else{
        Q->rear=Q-rear->next=N;
    }
    Q->size++;
    return 0;
}

int DeQ(Queue *Q,double *E){
    if(!Q->front){
        return 1;
    }
    else{
        Node *Front=Q->front;
        Q->fornt=Q->front->next;
        *E=Front->data;
        free(Front);
        Q->size--;
        if(!Q->size){
            Q->front=Q->rear=NULL;
        }
        return 0;
    }
}