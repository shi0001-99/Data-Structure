#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007LL

// 求两个数的绝对值差
long long absDiff(long long x, long long y) {
    if (x > y)
        return x - y;
    else
        return y - x;
}

// 在有序数组a中，寻找最接近x的数
long long findMinDiff(int a[], int n, long long x) {
    int left = 0, right = n - 1;

    // 二分查找第一个大于等于x的位置
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (a[mid] < x)
            left = mid + 1;
        else
            right = mid - 1;
    }

    // left是第一个大于等于x的位置
    long long ans = 1000000000000000000LL;

    // 检查left位置
    if (left < n) {
        long long d = absDiff(a[left], x);
        if (d < ans)
            ans = d;
    }

    // 检查left前一个位置
    if (left > 0) {
        long long d = absDiff(a[left - 1], x);
        if (d < ans)
            ans = d;
    }

    return ans;
}

int main() {
    int n;
    scanf("%d", &n);

    int *a = (int *)malloc(sizeof(int) * n);
    int *b = (int *)malloc(sizeof(int) * n);

    // 输入当前亮度
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // 输入目标亮度
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }

    long long sum = 0;
    long long maxReduce = 0;

    for (int i = 0; i < n; i++) {
        // 当前位置原来的误差
        long long oldDiff = absDiff(a[i], b[i]);

        // 当前目标亮度与a中最近的亮度值的误差
        long long newDiff = findMinDiff(a, n, b[i]);

        // 如果修改当前灯，最多能减少多少误差
        long long reduce = oldDiff - newDiff;

        // 更新最大减少量
        if (reduce > maxReduce)
            maxReduce = reduce;

        // 累加原始误差
        sum += oldDiff;
    }

    // 最小误差 = 原始误差 - 最大减少量
    long long ans = sum - maxReduce;

    // 先求最小值，再取模
    printf("%lld\n", ans % MOD);

    free(a);
    free(b);

    return 0;
}