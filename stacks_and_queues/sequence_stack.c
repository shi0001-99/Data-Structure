typedef struct{
    double *base;
    double *top;
    int size;
}stack;

void initstack(stack* s){
    s->base=(double*)calloc(6,sizeof(double));
    s->top=s->base;
    s->size=6;
}

int Push(stack* s,double e){
    if(s->top-s->base>=s->size){
        return 1;//err
    }

}
int Top(stack* s){
    if(s->top==s->base){
        return -1;//栈空，错误
    }
    return *(s->top-1);
}