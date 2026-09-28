//时间复杂度O(n*k)
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main() {
    int n, k;
    scanf_s("%d%d", &n, &k);
    int arr[100];
    for (int i = 0; i < n; i++) {
        scanf_s("%d", &arr[i]);
    }
    int maxnum = -10000;

    for (int i = 0; i < n - k + 1; i++) {
        for (int j = i; j < i + k; j++) {
            if (maxnum < arr[j]) {
                maxnum = arr[j];
            }
        }
        printf("%d", maxnum);
    }
    return 0;
}

//时间复杂度O(n)
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#include <stdio.h>
#include <stdlib.h>

/**
 * nums: 输入数组
 * numsSize: 数组长度
 * k: 窗口大小
 * returnSize: 输出结果的长度（通过指针返回）
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }

    // 结果数组最多有 numsSize - k + 1 个元素
    int* result = (int*)malloc(sizeof(int) * (numsSize - k + 1));
    // 单调队列：存下标，用数组模拟双端队列
    int* deque = (int*)malloc(sizeof(int) * numsSize);
    int head = 0;  // 队首指针
    int tail = 0;  // 队尾指针（指向下一个空位）
    int idx = 0;   // 结果数组下标

    for (int i = 0; i < numsSize; i++) {
        // 1. 队尾弹出所有比当前元素小的（它们不可能再成为最大值）
        while (tail > head && nums[deque[tail - 1]] <= nums[i]) {
            tail--;
        }
        // 当前元素下标入队
        deque[tail++] = i;

        // 2. 队首超出窗口范围则弹出
        if (deque[head] <= i - k) {
            head++;
        }

        // 3. 窗口形成后，队首就是当前窗口最大值
        if (i >= k - 1) {
            result[idx++] = nums[deque[head]];
        }
    }

    *returnSize = idx;
    free(deque);
    return result;
}

// 测试
int main() {
    int nums[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    int returnSize = 0;

    int* res = maxSlidingWindow(nums, 8, k, &returnSize);

    printf("结果: ");
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    free(res);
    return 0;
}