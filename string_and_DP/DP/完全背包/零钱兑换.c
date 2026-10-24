int change(int amount, int* coins, int coinsSize) {
    unsigned long dp[300][5005]={0};
    for(int i=0;i<coinsSize;i++){
        dp[i][0]=1;
    }
    for (int j = 0; j <= amount; j++) {
        if (j % coins[0] == 0) dp[0][j] = 1;
    }
    // 以下遍历顺序行列可以颠倒
    for (int i = 1; i < coinsSize; i++) { // 行，遍历物品
        for (int j = 1; j <= amount; j++) { // 列，遍历背包
            if (coins[i] > j) dp[i][j] = dp[i - 1][j]; 
            else dp[i][j] = dp[i - 1][j] +  dp[i][j - coins[i]];
        }
    }
    return dp[coinsSize-1][amount];
}