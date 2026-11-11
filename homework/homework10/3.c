#include <stdio.h>
#include <stdlib.h>

#define N 200005

typedef struct {
    int left;
    int right;
    long long diff;
} Pair;

Pair heap[N];
int size = 0;

int pre[N], next[N];
int a[N];
char sex[N];
int deleted[N];

// 比较两个配对的优先级
int Less(Pair x, Pair y) {
    if (x.diff != y.diff)
        return x.diff < y.diff;
    return x.left < y.left;
}

// 小顶堆向下调整
void MinHeapify(int i) {
    int l = 2 * i;
    int r = 2 * i + 1;
    int min = i;

    if (l <= size && Less(heap[l], heap[min]))
        min = l;

    if (r <= size && Less(heap[r], heap[min]))
        min = r;

    if (min != i) {
        Pair temp = heap[i];
        heap[i] = heap[min];
        heap[min] = temp;
        MinHeapify(min);
    }
}

// 插入一个配对
void EnQ(Pair x) {
    heap[++size] = x;
    int i = size;

    while (i > 1 && Less(heap[i], heap[i/2])) {
        Pair temp = heap[i];
        heap[i] = heap[i/2];
        heap[i/2] = temp;
        i /= 2;
    }
}

// 删除并返回堆顶
Pair DeQ() {
    Pair ans = heap[1];

    heap[1] = heap[size];
    size--;

    if (size > 0)
        MinHeapify(1);

    return ans;
}

// 将相邻且性别不同的两只小蓝鲸加入堆
void AddPair(int l, int r) {
    if (l == 0 || r == 0)
        return;

    if (sex[l] == sex[r])
        return;

    Pair p;
    p.left = l;
    p.right = r;

    long long d = (long long)a[l] - a[r];
    p.diff = d >= 0 ? d : -d;

    EnQ(p);
}

int main() {
    int n;
    scanf("%d", &n);

    scanf("%s", sex + 1);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    // 初始化双向链表
    for (int i = 1; i <= n; i++) {
        pre[i] = i - 1;
        next[i] = (i == n ? 0 : i + 1);
    }

    // 初始化小顶堆
    for (int i = 1; i < n; i++) {
        AddPair(i, i + 1);
    }

    int ansL[N], ansR[N];
    int count = 0;

    while (size > 0) {
        Pair p = DeQ();

        int l = p.left;
        int r = p.right;

        // 跳过已经失效的配对
        if (deleted[l] || deleted[r])
            continue;

        if (next[l] != r)
            continue;

        // 记录答案
        ansL[++count] = l;
        ansR[count] = r;

        // 标记删除
        deleted[l] = 1;
        deleted[r] = 1;

        // 找到这一对左右两侧的节点
        int L = pre[l];
        int R = next[r];

        // 从双向链表中删除 l 和 r
        if (L != 0)
            next[L] = R;

        if (R != 0)
            pre[R] = L;

        // 新产生的相邻组合
        AddPair(L, R);
    }

    printf("%d\n", count);

    for (int i = 1; i <= count; i++) {
        printf("%d %d\n", ansL[i], ansR[i]);
    }

    return 0;
}
