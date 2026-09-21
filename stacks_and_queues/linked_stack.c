typedef struct{
    Node *base;
    Node *top;
    int size;
}stack;//实际上是一个保持首尾指针的单链表

void initstack(stack* s){
    s->base=NULL;
    s->top=NULL;
    s->size=0;
}

