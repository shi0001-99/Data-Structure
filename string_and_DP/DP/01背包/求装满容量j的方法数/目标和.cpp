//回溯，暴力枚举

// 辅助递归函数
int dfs(int* nums, int numsSize, int target, int index, int currentSum) {
    // 终止条件：所有数字都处理完了
    if (index == numsSize) {
        // 如果结果等于 target，返回 1 种方案；否则返回 0
        return currentSum == target ? 1 : 0;
    }
    
    // 当前数字前加 '+'
    int add = dfs(nums, numsSize, target, index + 1, currentSum + nums[index]);
    // 当前数字前加 '-'
    int sub = dfs(nums, numsSize, target, index + 1, currentSum - nums[index]);
    
    // 返回两种选择的总和
    return add + sub;
}
// 主函数
int findTargetSumWays(int* nums, int numsSize, int target) {
    // 从第 0 个数字开始，当前和为 0
    return dfs(nums, numsSize, target, 0, 0);
}

//-----------------------------------------------------------------------------

//用nums 装满 容量为target的背包，有几种方法
//dp[i][j]：使用下标为[0, i]的nums[i]能够凑满j这么大容量的包，有dp[i][j]种方法
//装满背包容量为0的方法个数是1，即放0件物品
int findTargetSumWays(int* nums, int numsSize, int target) {
    int sum=0;
    for(int i=0;i<numsSize;i++){
        sum+=nums[i];
    }
    if ((target + sum) % 2 == 1) return 0;
    if(abs(target)>sum) return 0;
    int x=(target+sum)/2;

    int dp[25][1005]={0};

    dp[0][0]=1;
    if (nums[0] <= x) dp[0][nums[0]] = 1;
    int numZero = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 0) numZero++;
        dp[i][0] = (int) pow(2.0, numZero);
    }

    for(int i=1;i<numsSize;i++){
        for(int j=1;j<=x;j++){
            if (nums[i] > j) dp[i][j] = dp[i - 1][j]; 
            else dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i]];
        }
    }
    return dp[numsSize-1][x];
}

//--------------------------------------------------------------------
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) sum += nums[i];
        if (abs(target) > sum) return 0; // 此时没有方案
        if ((target + sum) % 2 == 1) return 0; // 此时没有方案

        int bagSize = (target + sum) / 2;
        
        vector<int> dp(bagSize + 1, 0);
        dp[0] = 1;//有一种方法，即什么都不装
        for (int i = 0; i < nums.size(); i++) {
            for (int j = bagSize; j >= nums[i]; j--) {
                dp[j] += dp[j - nums[i]];//根据二维数组压缩得到
            }
        }
        return dp[bagSize];
    }
};