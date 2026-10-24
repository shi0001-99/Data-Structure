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

//----------------------------------------------------------
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<uint64_t> dp(amount + 1, 0); // 防止相加数据超int
        dp[0] = 1; // 只有一种方式达到0
        for (int i = 0; i < coins.size(); i++) { // 遍历物品
            for (int j = coins[i]; j <= amount; j++) { // 遍历背包
                dp[j] += dp[j - coins[i]];
            }
        }
        return dp[amount]; // 返回组合数
    }
};
