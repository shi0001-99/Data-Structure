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

//--------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct node {
    int val;
    struct node* left;
    struct node* right;
}node;

int max(int a, int b) {
    if (a > b)return a;
    return b;
}

node* createnode(int val) {
    node* n = (node*)malloc(sizeof(node));
    n->val = val;
    n->left = NULL;
    n->right = NULL;
    return n;
}

node* buildtree() {
    int buf;
    if (scanf("%d", &buf) != 1 || buf == -1)return NULL;
    node* root = createnode(buf);
    node* que[10000];
    int head = 0, rear = 0;
    que[rear++] = root;
    while (head < rear) {
        node* parent = que[head++];
        if (scanf("%d", &buf) != 1)break;
        if (buf != -1) {
            parent->left = createnode(buf);
            que[rear++] = parent->left;
        }
        if (scanf("%d", &buf) != 1)break;
        if (buf != -1) {
            parent->right = createnode(buf);
            que[rear++] = parent->right;
        }
    }
    return root;
}

int balance(node* root) {
    if (!root)return 0;
    int left = balance(root->left);
    if (left == -1)return -1;
    int right = balance(root->right);
    if (right == -1)return -1;
    if (left - right > 1 || left - right < -1)return -1;
    return max(left, right) + 1;
}

int search(node* root, int* pre) {
    if (!root) return 1;
    if (!search(root->left, pre)) return 0;
    if (*pre > root->val) return 0;
    *pre = root->val;
    if (!search(root->right, pre)) return 0;
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    node* root = buildtree();
    int pre = INT_MIN;
    if (balance(root) == -1 || search(root, &pre) == 0) {
        printf("no");
    }
    else printf("yes");
}