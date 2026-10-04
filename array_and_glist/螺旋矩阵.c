#include <stdio.h>

#define ROWS 4
#define COLS 4

// 螺旋遍历矩阵
void spiralOrder(int matrix[ROWS][COLS]) {
    if (ROWS == 0 || COLS == 0) return;

    int L = 0;
    int R = COLS - 1;
    int T = 0;
    int B = ROWS - 1;

    printf("螺旋遍历结果: ");

    while (L <= R && T <= B) {
        // 1. Print M[T][L] ... M[T][R] (从左到右)
        for (int i = L; i <= R; i++) {
            printf("%d ", matrix[T][i]);
        }
        T++; // 上边界下移

        // 2. Print M[T][R] ... M[B][R] (从上到下)
        for (int i = T; i <= B; i++) {
            printf("%d ", matrix[i][R]);
        }
        R--; // 右边界左移

        // 3. Print M[B][R] ... M[B][L] (从右到左)
        // 注意：需要判断 T <= B，防止单行矩阵重复遍历
        if (T <= B) {
            for (int i = R; i >= L; i--) {
                printf("%d ", matrix[B][i]);
            }
            B--; // 下边界上移
        }

        // 4. Print M[B][L] ... M[T][L] (从下到上)
        // 注意：需要判断 L <= R，防止单列矩阵重复遍历
        if (L <= R) {
            for (int i = B; i >= T; i--) {
                printf("%d ", matrix[i][L]);
            }
            L++; // 左边界右移
        }
    }
    printf("\n");
}

