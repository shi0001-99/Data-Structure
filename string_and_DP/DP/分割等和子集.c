int max(int a,int b){
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}
bool canPartition(int* nums, int numsSize) {
    int sum=0;
    for(int i=0;i<numsSize;i++){
        sum+=nums[i];
    }
    if(sum%2==1){
        return false;
    }
    int target=sum/2;
    int dp[10005]={0};
    for(int i=0;i<numsSize;i++){
        for(int j=target;j>=nums[i];j--){
            dp[j]=max(dp[j],dp[j-nums[i]]+nums[i]);
        }
    }
    if(dp[target]==target){
        return true;
    }
    return false;
}