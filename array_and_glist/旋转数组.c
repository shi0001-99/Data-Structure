void rotate(int matrix[N][N]) {
    int L = 0;
    int R = N - 1;
    int T = 0;
    int B = N - 1;

    // 逐层处理（由外向内）
    while (L < R && T < B) {
        // 遍历当前层上边的每一个元素
        
        // i 是相对于左边界的偏移量
        for (int i = 0; i < R - L; i++) {
            // 保存左上角的元素（因为后面会被覆盖）
            int temp = matrix[T][L + i];

            // 按照图片的公式进行四元组交换
            // 1. 左下 -> 左上
            matrix[T][L + i] = matrix[B - i][L];
            // 2. 右下 -> 左下
            matrix[B - i][L] = matrix[B][R - i];
            // 3. 右上 -> 右下
            matrix[B][R - i] = matrix[T + i][R];
            // 4. 左上(已保存在temp) -> 右上
            matrix[T + i][R] = temp;
        }

        // 缩进边界，处理下一层
        L++;
        R--;
        T++;
        B--;
    }
}
 
