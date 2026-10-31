/*小蓝鲸想给同学们表演卡牌魔术.
拿到任意一堆牌, 小蓝鲸会先用高超的手法进行洗牌, 将牌排列成某个特定顺序后, 开始表演.
每次他会移除牌堆第一张牌, 并将其展示；然后将剩余牌的第一张放至牌堆底部. 如此反复, 直到所有牌均被移除并展示.
小蓝鲸期望保证牌被展示的顺序恰好是牌面值的升序排列, 请你求出若要达到此效果, 洗牌后牌的排列顺序.
牌的牌面值为整数, 但不限于1-13或1-54的范围, 牌堆中没有重复的牌, 牌的牌面值也不一定连续.
输入：两行, 第一行一个数字N, 代表卡牌的数量；
第二行N个数字, 空格分隔, 分别代表N张牌的编号, 按升序（即小蓝鲸期望展示的顺序）给出.
4
1 2 3 4
输出：1 3 2 4

解释解释：初始时, 移除并展示1, 剩余的[3,2,4]中, 3被移到末尾变为[2,4,3]； 接下来, 移除并展示2, 剩余的[4,3]中, 4被移到末尾变为[3,4]； 接下来, 移除并展示3, 最后移除并展示4. 这样, 牌被展示的顺序恰好是[1,2,3,4]这样的升序排列.
*/
#include <stdio.h>

int a[1000001];
int q[1000001];

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    int front = n;
    int rear = n;
    for (int i = n - 1; i >= 0; i--)
    {
        if (front != rear)
        {
            int last = q[rear - 1];
            rear--;
            front--;
            q[front] = last;
        }
        q[--front] = a[i];
    }

    for (int i = front; i < rear; i++)
    {
        if (i > front) printf(" ");
        printf("%d", q[i]);
    }
    printf("\n");
    return 0;
}

//---------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    scanf("%d", &N);

    long long *src = malloc(sizeof(long long) * N);  // 只读输入，最终展示的顺序
    long long *cur = malloc(sizeof(long long) * N);  // 工作牌堆

    for (int i = 0; i < N; i++) {
        scanf("%lld", &src[i]);
    }

    int size = 0;  // cur 中当前牌堆大小

    // 从最后一张牌开始倒推
    for (int i = N - 1; i >= 0; i--) {

        // 第一步：把 cur 中最后一张牌移到最前面
        if (size > 0) {
            long long last = cur[size - 1];
            for (int j = size - 1; j > 0; j--) {
                cur[j] = cur[j - 1];
            }
            cur[0] = last;
        }

        // 第二步：把 src[i] 放到最前面
        for (int j = size; j > 0; j--) {
            cur[j] = cur[j - 1];
        }
        cur[0] = src[i];

        size++;
    }

    for (int i = 0; i < N; i++) {
        if (i > 0) printf(" ");
        printf("%lld", cur[i]);
    }
    printf("\n");

    free(src);
    free(cur);
    return 0;
}