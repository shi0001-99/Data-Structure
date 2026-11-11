
#include <stdio.h>
#include <stdlib.h>

void MaxHeapify(int *A,int size,int i){
    int l=2*i;
    int r=2*i+1;
    int max=i;

    if(l<=size && A[l]>A[max]){
        max=l;
    }
    if(r<=size && A[r]>A[max]){
        max=r;
    }

    if(max!=i){
        int temp=A[i];
        A[i]=A[max];
        A[max]=temp;
        MaxHeapify(A,size,max);
    }
}

void CreateQ(int *A,int size){
    for(int i=size/2;i>=1;i--){
        MaxHeapify(A,size,i);
    }
}

int DeQ(int *A,int size){
    int Max=A[1];
    A[1]=A[size];
    MaxHeapify(A,size-1,1);
    return Max;
}

void IncreaseVal(int *A,int i,int x){
    A[i]=x;
    while(i>1 && A[i/2]<A[i]){
        int temp=A[i];
        A[i]=A[i/2];
        A[i/2]=temp;
        i=i/2;
    }
}

void EnQ(int *A,int size,int x){
    A[size+1]=x;
    IncreaseVal(A,size+1,x);
}

int main(){
    int n,k;
    scanf("%d%d",&n,&k);

    int a[100005];

    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }

    CreateQ(a,n);

    int curr=n;

    for(int i=0;i<k;i++){
        int val=DeQ(a,curr);
        curr--;

        EnQ(a,curr,val/2);
        curr++;
    }

    long long sum=0;

    for(int i=1;i<=n;i++){
        sum+=a[i];
    }

    printf("%lld",sum);
    return 0;
}
