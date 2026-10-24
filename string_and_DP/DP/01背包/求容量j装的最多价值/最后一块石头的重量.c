int max(int a,int b){
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}
int lastStoneWeightII(int* stones, int stonesSize) {
    int sum=0;
    for(int i=0;i<stonesSize;i++){
        sum+=stones[i];
    }
    int target=sum/2;
    int dp[1505];
    for(int i=0;i<stonesSize;i++){
        for(int j=target;j>=stones[i];j--){
            dp[j]=max(dp[j],dp[j-stones[i]]+stones[i]);
        }
    }
    return sum-2*dp[target];
}