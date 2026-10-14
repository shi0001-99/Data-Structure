#include <stdio.h>

int a[1000005], b[1000005], sum[1000005];

// 交换三个数组的第 i、j 个元素
void swap(int i, int j) {
    int t;
    t = sum[i]; sum[i] = sum[j]; sum[j] = t;
    t = a[i];   a[i]   = a[j];   a[j]   = t;
    t = b[i];   b[i]   = b[j];   b[j]   = t;
}

// 快排：按 sum 从大到小
void quickSort(int l, int r) {
    if (l >= r) return;
    int mid = sum[(l + r) / 2];
    int i = l, j = r;
    while (i <= j) {
        while (sum[i] > mid) i++;   // 左边找比 mid 小的
        while (sum[j] < mid) j--;   // 右边找比 mid 大的
        if (i <= j) {
            swap(i, j);
            i++;
            j--;
        }
    }
    quickSort(l, j);
    quickSort(i, r);
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < n; i++) scanf("%d", &b[i]);
    for (int i = 0; i < n; i++) sum[i] = a[i] + b[i];

    quickSort(0, n - 1);

    long long scoreA = 0, scoreB = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) scoreA += a[i];   // A 取第 0、2、4… 个
        else            scoreB += b[i];   // B 取第 1、3、5… 个
    }

    if (scoreA > scoreB)      printf("1\n");
    else if (scoreA < scoreB) printf("-1\n");
    else                      printf("0\n");

    return 0;
}