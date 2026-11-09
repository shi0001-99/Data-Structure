//堆是一个完全二叉树，且每个节点的值都小于等于（大于等于）其子节点的值
//root->val<=root->child->val 最小堆
//root->val>=root->child->val 最大堆

//最小堆化 MinHeapify 时间复杂度O(h)
void MinHeapify(int *A,int size,int i){
    int l=2*i;
    int r=2*i+1;
    int min=i;
    if(l<=size && A[l]<A[min]){
        min=l;
    }
    if(r<=size && A[r]<A[min]){
        min=r;
    }
    if(min!=i){
        int temp=A[i];
        A[i]=A[min];
        A[min]=temp;
        MinHeapify(A,size,min);
    }
}

//创建最小堆  时间复杂度O(n)
void CreateQ(int *A,int size){
    for(int i=n/2;i>=1;i--){//i的孩子都是最小堆(叶子节点)
        MinHeapify(int *A,int size,i);//O(h)
    }
}
//但是均摊时间复杂度是O(n),因为大量操作都是在底部完成的，此时的高度还不高


//删除最小元素  时间复杂度O(h)
int DeQ(int *A,int size){
    int Min=A[i];
    A[1]=A[size];//把最后一个元素放到第一个的位置
    MinHeapify(A,size-1,1);
    return Min;
}

//减少最小堆中元素的数值  时间复杂度O(h)
int DecreaseVal(int *A,int size,int i,int x){
    assert(x<A[i]);
    A[i]=x;
    while(i>1 && A[i/2]>A[i]){
        int temp=A[i];
        A[i]=A[i/2];
        A[i/2]=temp;
    }
}

//插入元素  时间复杂度O(h)
void EnQ(int *A,int size,int x){
    A[size+1]=INT_MAX;
    DecreaseVal(A,size+1,size+1,x);
}