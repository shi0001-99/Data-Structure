#include<stdio.h>
typedef char ElemType;

typedef struct TreeNode{
    ElemType data;
    TreeNode *lchild;
    TreeNode *rchild;
}TreeNode;

typedef TreeNode* BiTree;

void preOrder(BiTree T){
    if(T==NULL){
        return;
    }
    printf("%c",T->data);
    preOrder(T->lchild);
    preOrder(T->rchild); 
}

void inOrder(BiTree T){
    if(T==NULL){
        return ;
    }
    preOrder(T->lchild);
    printf("%c",T->data);
    preOrder(T->rchild); 
}

void postOrder(BiTree T){
    if(T==NULL){
        return ;
    }
    preOrder(T->lchild);
    preOrder(T->rchild); 
    printf("%c",T->data);
}
int main(){
    return 0;
}