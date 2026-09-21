typedef struct{
    Node *base;
    Node *top;
    int size;//栈当前的大小
}stack;//实际上是一个保持首尾指针的单链表

void initstack(stack* s){
    s->base=NULL;
    s->top=NULL;
    s->size=0;
}

int Push(stack* s,double e){
    Node *N=(Node*)malloc(sizeof(Node));
    N->data=e;
    N->next=s->top;
    if(!s->base){
        s->base=s->top=N;
    }
    else{
        s->top=N;
    }
    s->size++;
    return 0;
}

//十进制转换八进制
void dec2oct(stack* s,int n){
    while(n){
        Push(s,n%8);
        n/=8;
    }
    while(!stackempty(s)){
        int e;
        Pop(s,&e);
        printf("%d",e);
    }
}

//括号匹配
