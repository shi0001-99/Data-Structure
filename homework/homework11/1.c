#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
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

int isBST(Node* root,int min_val, int max_val) {
    if (root == NULL) return 1;
    
    // 如果当前节点的值不在合法范围内，则不是 BST
    if (root->data <= min_val || root->data >= max_val) return 0;
    
    return isBST(root->left, min_val, root->data) && 
           isBST(root->right, root->data, max_val);
}

int isAVL(Node* root) {
    if (root == NULL) return 0;
    
    int left_h = isAVL(root->left);
    if (left_h == -1) return -1; // 左子树不平衡
    
    int right_h = isAVL(root->right);
    if (right_h == -1) return -1; // 右子树不平衡
    
    // 检查当前节点平衡因子
    if (left_h - right_h > 1 ||left_h - right_h < -1) return -1;
    
    // 返回当前树的高度
    return (left_h > right_h ? left_h : right_h) + 1;
}

int main(){
    int n;
    scanf("%d",&n);

    Node* q[10000];
    int front=0,rear=0;
    int c;
    scanf(" %d",&c);
    if(c==-1){
        printf("yes\n");
        return 0;
    }
    Node* root=create(c);
    q[rear++]=root;

    while(front<rear){
        Node* p=q[front++];
        if(scanf(" %d",&c)!=1){
            break;
        }
        if(c!=-1){
            p->left=create(c);
            q[rear++]=p->left;
        }

        if (scanf(" %d", &c) != 1){
            break;
        }
        if (c !=-1) {
            p->right = create(c);
            q[rear++] = p->right;
        }
    }

    if (!isBST(root, INT_MIN, INT_MAX)) {
        printf("no\n");
        return 0;
    }
    
    if (isAVL(root) == -1) {
        printf("no\n");
        return 0;
    }
    
    printf("yes\n");
    return 0;
}