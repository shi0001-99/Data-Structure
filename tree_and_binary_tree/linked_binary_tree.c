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

//---------------------------------------------------------
/*
1.二叉树第i层 最多2^(i-1)个节点
2.深度为k的二叉树 最多包含2^k-1个节点
3.对于任意一颗(二叉)树 若包含n个节点m条边 则m=n-1
4.对于任何一个二叉树 若其包含n0个叶子节点 n2个度为2的节点 则n0=n2+1
   m=n1+2*n2=n-1
5.完全二叉树里面 度为1的节点的个数为0或1
6.具有n个节点的完全二叉树的深度为floor(log 2 n)+1

顺序存储
7.对于一个二叉树 从上到下 从左到右 从1开始编号
  对一个编号为i的节点 父节点是floor(i/2)
                    左子节点是2i
                    右子节点是21+1
                    (考虑是否越界)
*/

先序 A B C D E F G H K 深度优先搜素 使用栈
中序 B D C A E H G K F 
后序 D C B H K G F E A

void PreOrderTraverse(TreeNode *Root){
    if(!Root){
        return ;
    }
    Stack S;
    Push(&S,Root);
    while(!Empty(&S)){
        TreeNode *TopNode=Top(&S);
        Pop(&S);
        visit(TopNode);
        if(TopNode->right){
            Push(&S,TopNode->right);
        }
        if(TopNode->left){
            Push(&S,TopNode->left);
        }
    }
}

void PostOrderTraverse(TreeNode *Root){
    if(!Root){
        return ;
    }
    Stack S1,S2;
    Push(&S1,Root);
    while(!Empty(&S1)){
        TreeNode *TopNode=Top(&S1);
        Pop(&S1);
        Push(&S2,TopNode);
        if(TopNode->left){
            Push(&S1,TopNode->left);
        }
        if(TopNode->right){
            Push(&S1,TopNode->right);
        }
    }
    while(!Empty(&S2)){
        visit(Top(&S2));
        Pop(&S2);
    }
}

int Depth(TreeNode* N){
    if(!N){
        return 0;
    }
    return max(Depth(N->left),Depth(N->right))+1;  
}