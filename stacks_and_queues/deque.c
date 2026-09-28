//额外操作：从队头插入，从队尾删除

//指针减法 Q->rear=Q->rear?(Q->rear-1):Q->size-1;
//        Q->front=Q->front?(Q->front-1):Q->size-1;

//从队尾删除 RearPrev=Q->rear->prev; //注意Q->rear==NULL的情况
//          free(Q->rear);
//          RearPrev->next=NULL; 注意RearPrev==NULL的情况
//          Q->rear=RearPrev;