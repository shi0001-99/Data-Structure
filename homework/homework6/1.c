//小蓝鲸数岛屿
#include <stdio.h>
#define MAXN 305
char grid[MAXN][MAXN];
int m, n;

// 深度优先搜索函数
void dfs(int r, int c) {
    //边界条件检查：越界或者当前格子不是陆地（'1'），直接返回
    if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] != '1') {
        return;
    }
    
    
    // 将当前陆地标记为已访问（改为 '0'）
    grid[r][c] = '0';
    
    // 向上下左右四个方向递归搜索
    dfs(r - 1, c); // 上
    dfs(r + 1, c); // 下
    dfs(r, c - 1); // 左
    dfs(r, c + 1); // 右
}

int main() {
    // 读取行数和列数
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf(" %c", &grid[i][j]);
        }
    }
    
    int island_count = 0;
    
    // 遍历整个地图
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // 发现新的岛屿
            if (grid[i][j] == '1') {
                island_count++;
                // 使用 DFS 将与当前陆地相连的所有陆地都标记为 '0'
                dfs(i, j);
            }
        }
    }
    
   
    printf("%d\n", island_count);
    
    return 0;
}