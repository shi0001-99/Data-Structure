#include<stdio.h>
#include<stdlib.h>

typedef char ElemType;

typedef struct ThreadNode{
    ElemType data;
    ThreadNode *lchild;
    ThreadNode *rchild;
    int ltag;
    int rtag;
}ThreadNode;

typedef ThreadNode* ThreadTree;

char str[]="ABDH##I##EJ###CF##G##";
int idx=0;

ThreadTree prev;

void createTree(ThreadTree *T){
    ElemType ch;
    ch=str[idx++];
    if(ch=='#'){
        *T=NULL;
    }
    else{
        *T=(ThreadTree*)malloc(sizeof(ThreadNode));
        *T->data=ch;
        createTree(&(*T)->lchild);
        if((*T)->lchild!=NULL){
            (*T)->ltag=0;
        }
        createTree(&(*T)->rchild);
        if((*T)->rchild!=NULL){
            (*T)->rtag=0;
        }
    }
}
int main(){
    ThreadTree head;
    ThreadTree T;
    createTree(&T);
    inOrderThreading(&head,T);
    inOrder(head);
    return 0;
}
