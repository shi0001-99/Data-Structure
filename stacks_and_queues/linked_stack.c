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
int CheckBrackets(char *str) {
    Stack S;
    InitStack(&S);
    char topChar;
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        // 左括号入栈
        if (c == '(' || c == '[' || c == '{') {
            if (!Push(&S, c)) {
                printf("栈溢出\n");
                return 0;
            }
        }
        // 右括号
        else if (c == ')' || c == ']' || c == '}') {
            // 栈空，右括号多了
            if (StackEmpty(&S)) {
                return 0;
            }
            Pop(&S, &topChar);
            // 栈顶左括号与当前右括号不匹配
            if (!Match(topChar, c)) {
                return 0;
            }
        }      
    }
    return StackEmpty(&S);
}