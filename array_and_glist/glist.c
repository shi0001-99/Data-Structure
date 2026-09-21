D=(a,(d,(e)))
B=(a,B)=(a,(a,(a,())))
//广义表是一个线性表，其元素可以是原子或者另一个广义表

//非空广义表均可分解成表头/表尾
LS=(a0,a1,a2,...,an-1)
Head(LS)=a0
Tail(LS)=(a1,...,an-1)//把剩余部分套个括号

typedef struct Node{
    int tag;
    union{
        AtomType atom;
        struct{
            struct Node *hp,*tp;
        }ptrs;
    }data;
}Node;

//打印操作
void printNode(Node *x){
    if(!x) return ;
    if(!x->tag){
        printf("%d",x->data.atom)
        return ;
    }
    printf("(");
    Node* hp=x->data.ptrs.hp;
    Node* tp=x->data.ptrs.tp;
    printNode(hp);
    printTail(tp);
    printf(")");
}
void printTail(Node* x){
    if(!x) return ;
    printf(",");
    printNode(x->data.ptrs.hp);
    printTail(x->data.ptrs.tp);
}