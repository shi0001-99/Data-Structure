//小蓝鲸的和谐队伍
#include<stdlib.h>
#include<stdio.h>
#define MAXN 1000005
int a[MAXN];
// 单调队列：存储下标
int max_q[MAXN];  // 队首是当前最大值
int min_q[MAXN];  // 队首是当前最小值

int main() {
    int n, limit;
    scanf("%d %d", &n, &limit);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }



    int max_head = 0, max_tail = 0;  //max_q的头尾指针
    int min_head = 0, min_tail = 0;  //min_q的头尾指针

    int left = 0;
    int ans = 0;

    for (int right = 0; right < n; right++) {
        // 1. 维护最大值单调队列（递减）
        while (max_head < max_tail && a[max_q[max_tail - 1]] <= a[right]) {
            max_tail--;
        }
        max_q[max_tail++] = right;

        // 2. 维护最小值单调队列（递增）
        while (min_head < min_tail && a[min_q[min_tail - 1]] >= a[right]) {
            min_tail--;
        }
        min_q[min_tail++] = right;

        // 3. 如果当前窗口不满足条件，移动左指针
        while (a[max_q[max_head]] - a[min_q[min_head]] > limit) {
            // 如果左指针指向的是队列头，需要弹出
            if (max_q[max_head] == left) max_head++;
            if (min_q[min_head] == left) min_head++;
            left++;
        }

        // 4. 更新答案
        int len = right - left + 1;
        if (len > ans) ans = len;
    }

    printf("%d\n", ans);
    return 0;
}