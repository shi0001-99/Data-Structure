#include <stdio.h>

int n, D;
long long w[100005];

// 判断载重量capacity是否能在D天内完成运输
int check(long long capacity) {
    int days = 1;
    long long current = 0;

    for (int i = 0; i < n; i++) {
        // 如果单个物资就超过载重量，无法运输
        if (w[i] > capacity)
            return 0;

        // 如果今天还能装下
        if (current + w[i] <= capacity) {
            current += w[i];
        }
        else {
            // 今天装不下，换到下一天
            days++;
            current = w[i];
        }
    }

    // 判断是否在规定天数内完成
    return days <= D;
}

int main() {
    scanf("%d %d", &n, &D);

    long long sum = 0;
    long long maxWeight = 0;

    for (int i = 0; i < n; i++) {
        scanf("%lld", &w[i]);

        sum += w[i];

        if (w[i] > maxWeight)
            maxWeight = w[i];
    }

    // 二分查找最小载重量
    long long left = maxWeight;
    long long right = sum;
    long long ans;

    while (left <= right) {
        long long mid = left + (right - left) / 2;

        if (check(mid)) {
            // mid可以完成运输，尝试更小的载重量
            ans = mid;
            right = mid - 1;
        }
        else {
            // mid太小，需要增加载重量
            left = mid + 1;
        }
    }

    printf("%lld\n", ans);

    return 0;
}