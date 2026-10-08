#include <stdio.h>
#include <stdbool.h>

void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
    if (matrix == NULL || matrixSize == 0 || matrixColSize == NULL || matrixColSize[0] == 0) {
        return;
    }
    
    int m = matrixSize;
    int n = matrixColSize[0];
    
    // 1. 记录第一行和第一列原本是否包含 0
    bool row0_has_zero = false;
    bool col0_has_zero = false;
    
    for (int j = 0; j < n; j++) {
        if (matrix[0][j] == 0) {
            row0_has_zero = true;
            break;
        }
    }
    
    for (int i = 0; i < m; i++) {
        if (matrix[i][0] == 0) {
            col0_has_zero = true;
            break;
        }
    }
    
    // 2. 使用第一行和第一列作为标记数组
    // 遍历除第一行和第一列以外的所有元素
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (matrix[i][j] == 0) {
                matrix[i][0] = 0; // 标记该行需要置零
                matrix[0][j] = 0; // 标记该列需要置零
            }
        }
    }
    
    // 3. 根据标记置零（除第一行和第一列以外的元素）
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                matrix[i][j] = 0;
            }
        }
    }
    
    // 4. 最后处理第一行和第一列
    if (row0_has_zero) {
        for (int j = 0; j < n; j++) {
            matrix[0][j] = 0;
        }
    }
    
    if (col0_has_zero) {
        for (int i = 0; i < m; i++) {
            matrix[i][0] = 0;
        }
    }
}