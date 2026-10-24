#include <stdio.h>

#define MAX_N 10005
#define MAX_K 10005

int coins[MAX_N][MAX_K]; // 存每个罐子的硬币
int counts[MAX_N];       // 存每个罐子的硬币数
long long dp[MAX_K];     // dp[w] 表示拿 w 枚硬币的最大收益

// 求最大值
long long max(long long a, long long b) {
    return a > b ? a : b;
}

int main() {
    int n, k;
    
    scanf("%d %d", &n, &k);

    
    for (int i = 0; i < n; i++) {
        scanf("%d", &counts[i]);
        for (int j = 0; j < counts[i]; j++) {
            scanf("%d", &coins[i][j]);
        }
    }


    for (int w = 0; w <= k; w++) {
        dp[w] = -1e18; 
    }
    dp[0] = 0;


    for (int i = 0; i < n; i++) {
        
        long long prefix_sum[MAX_K] = {0};
        for (int j = 1; j <= counts[i]; j++) {
            prefix_sum[j] = prefix_sum[j - 1] + coins[i][j - 1];//把当前罐子的前缀算出来
        }

        
        for (int w = k; w >= 0; w--) {//目前还能再拿w个硬币

            for (int j = 1; j <= counts[i] && j <= w; j++) {//在当前罐子拿j个硬币
                if (dp[w - j] != -1e18) { 
                    dp[w] = max(dp[w], dp[w - j] + prefix_sum[j]);
                }
            }
        }
    }


    long long ans = 0;
    for (int w = 0; w <= k; w++) {
        if (dp[w] > ans) {
            ans = dp[w];
        }
    }

    printf("%lld\n", ans);
    return 0;
}