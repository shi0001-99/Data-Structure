#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* left,*right;
}Node;

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
}