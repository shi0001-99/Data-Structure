#include <stdio.h>

#define N 100005

int L[N], R[N];
int ls = 0, rs = 0;//元素个数

// 大顶堆插入
void PushMax(int x){
    int i = ++ls;//末尾位置
    while(i > 1 && L[i/2] < x){
        L[i] = L[i/2];
        i /= 2;
    }
    L[i] = x;
}

// 小顶堆插入
void PushMin(int x){
    int i = ++rs;
    while(i > 1 && R[i/2] > x){
        R[i] = R[i/2];
        i /= 2;
    }
    R[i] = x;
}

// 大顶堆删除堆顶
int PopMax(){
    int ans = L[1];
    int x = L[ls--];
    int i = 1, child;

    while(2*i <= ls){
        child = 2*i;
        if(child+1 <= ls && L[child+1] > L[child])
            child++;

        if(x >= L[child]) break;

        L[i] = L[child];
        i = child;
    }
    if(ls > 0) L[i] = x;
    return ans;
}

// 小顶堆删除堆顶
int PopMin(){
    int ans = R[1];
    int x = R[rs--];
    int i = 1, child;

    while(2*i <= rs){
        child = 2*i;
        if(child+1 <= rs && R[child+1] < R[child])
            child++;

        if(x <= R[child]) break;

        R[i] = R[child];
        i = child;
    }
    if(rs > 0) R[i] = x;
    return ans;
}

int main(){
    int n, x;
    scanf("%d", &n);

    for(int i=1; i<=n; i++){
        scanf("%d", &x);

        if(ls == 0 || x <= L[1])
            PushMax(x);
        else
            PushMin(x);

        // 调整两个堆的大小
        if(ls > rs+1)
            PushMin(PopMax());

        if(ls < rs)
            PushMax(PopMin());

        // 奇数个元素时输出中位数
        if(i % 2 == 1)
            printf("%d\n", L[1]);
    }

    return 0;
}
