#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* left,*right;
}Node;

typedef struct QItem{
    Node* node;
    long long idx;
}QItem;

Node* create(int x){
    Node* p=(Node*)malloc(sizeof(Node));
    p->data=x;
    p->left=p->right=NULL;
    return p;
}

int main(){
    Node* q[10000];
    int front=0,rear=0;
    char c;
    scanf(" %c",&c);
    if(c=='n'){
        return 0;
    }
    Node* root=create(c-'0');
    q[rear++]=root;

    while(front<rear){
        Node* p=q[front++];
        if(scanf(" %c",&c)!=1){
            break;
        }
        if(c!='n'){
            p->left=create(c-'0');
            q[rear++]=p->left;
        }

        if (scanf(" %c", &c) != 1){
            break;
        }
        if (c != 'n') {
            p->right = create(c - '0');
            q[rear++] = p->right;
        }
    }

    QItem queue[10000];
    int front=0,rear=0;

    queue[front++]=QItem{root,1};
    long long maxWidth=0;
    while(front<rear){
        int sz=rear-front;
        long long left=queue[front].idx;
        long long right;
        for(int i=0;i<sz;i++){
            QItem cur=queue[front++];
            right=cur.idx;
            if(cur.node->left){
                q[rear++] = (QItem){cur.node->left, cur.idx * 2};
            }
            if(cur.node->right){
                q[rear++] = (QItem){cur.node->right, cur.idx * 2 + 1};
            }
        }
        long long w=right-left+1;
        if(w>maxWidth){
            maxWidth=w;
        }
    }
    printf("%lld",maxWidth);
}
