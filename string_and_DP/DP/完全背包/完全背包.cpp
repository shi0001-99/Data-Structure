//完全背包：一种物品有无限个
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, bagWeight;
    int w, v;
    cin >> n >> bagWeight;
    vector<int> weight(n);
    vector<int> value(n);
    for (int i = 0; i < n; i++) {
        cin >> weight[i] >> value[i];
    }

    vector<vector<int>> dp(n, vector<int>(bagWeight + 1, 0));

    // 初始化
    for (int j = weight[0]; j <= bagWeight; j++)
        dp[0][j] = dp[0][j - weight[0]] + value[0];//能装下就一直装物品0

    for (int i = 1; i < n; i++) { // 遍历物品
        for(int j = 0; j <= bagWeight; j++) { // 遍历背包容量
            if (j < weight[i]) dp[i][j] = dp[i - 1][j];//一个物品i都放不了
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - weight[i]] + value[i]);//完全不放物品i 和 放物品i
        }
    }

    cout << dp[n - 1][bagWeight] << endl;

    return 0;
}

//---------------------------------------------------------