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

int dfs(Node *root, int *ans)
{
    if (root == NULL)
        return 0;

    /* 先计算左子树和右子树 */
    int left = dfs(root->left, ans);
    int right = dfs(root->right, ans);

    int leftLen = 0;
    int rightLen = 0;

    /* 如果左孩子和当前节点值相同，可以接上 */
    if (root->left != NULL &&
        root->left->data == root->data)
    {
        leftLen = left + 1;
    }

    /* 如果右孩子和当前节点值相同，可以接上 */
    if (root->right != NULL &&
        root->right->data == root->data)
    {
        rightLen = right + 1;
    }

    /* 
       最长路径可能经过当前节点，
       所以左边 + 右边
    */
    if (leftLen + rightLen > *ans)
    {
        *ans = leftLen + rightLen;
    }

    /*
       返回给父节点时只能选一边
    */
    if (leftLen > rightLen)
        return leftLen;
    else
        return rightLen;
}

int ans=0;

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

    dfs(root, &ans);
    printf("%d\n", ans);
    return 0;
}