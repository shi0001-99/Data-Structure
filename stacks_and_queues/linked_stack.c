typedef struct{
    Node *base;
    Node *top;//指向栈顶元素
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

int Pop(stack* s,double *e){
    if(!s->base){
        return 1;//err
    }
    else{
        Node* Top=s->top;
        s->top=Top->next;
        *e=Top->data;
        free(Top);
        s->size--;
        if(!s->size){
            s->top=s->base=NULL;
        }
        return 0;
    }
}

//-------------------------------------
//十进制转换八进制
void dec2oct(stack* s,int n){
    while(n){
        Push(s,n%8);
        n/=8;
    }//压栈，倒序存储
    while(!stackempty(s)){
        int e;
        Pop(s,&e);
        printf("%d",e);
    }//弹栈，输出为正序
}

//-------------------------------------
//行编辑问题
void LineEdit(stack *s){
    char c=getchar();
    while(c!='enter'){
        switch(c){
            case 'a'-'z': Push(s,c); break;
            case 'backspace': Pop(s,&c); break;
        }
        c=getchar();
    }
    ClearStack(s);
}

//-------------------------------------
//最小栈  用另外一个栈来存储当前最小值

//-------------------------------------
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
    return StackEmpty(&S);//最后如果栈空，返回True
}


//迷宫求解

/*表达式求值
前缀表达式求值：操作数和数压栈，自底向上观察栈顶3个元素，若是前缀式就出栈求值再压栈
for (int i = 0; i < tokenCount; i++) {
        // 先无脑入栈
        push(&s, tokens[i]);
        // 自底向上观察栈顶 3 个元素（即检查栈顶的3个元素是否构成 "运算符 操作数 操作数"）
        // 注意：这里的顺序是 s.top-2 (运算符), s.top-1 (左操作数), s.top (右操作数)
        while (s.top >= 2) {
            char *top1 = s.data[s.top];       // 右操作数
            char *top2 = s.data[s.top - 1];   // 左操作数
            char *top3 = s.data[s.top - 2];   // 运算符
            // 如果栈顶3个元素满足：运算符 操作数 操作数
            if (isOperator(top3) && !isOperator(top2) && !isOperator(top1)) {
                // 弹出这3个元素
                char op[20], opA[20], opB[20];
                pop(&s, opB); // 右操作数
                pop(&s, opA); // 左操作数
                pop(&s, op);  // 运算符
                
                // 转换为数字并计算
                double a = atof(opA);
                double b = atof(opB);
                double result = calculate(op, a, b);
                
                // 将计算结果转回字符串，重新压入栈中
                char resultStr[20];
                sprintf(resultStr, "%.2f", result); // 保留两位小数
                push(&s, resultStr);
            } else {
                // 如果不满足条件，说明当前栈顶3个元素不能归约，停止检查
                break;
            }
        }
    }

后缀表达式求值：操作数和数压栈，自底向上观察栈顶3个元素，若是后缀式就出栈求值再压栈
*/



//开关布线盒（类似于括号匹配）
//最小栈（多用一个栈去存储最小值）
//直方图中的最大矩形