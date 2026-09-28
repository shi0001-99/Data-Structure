#include <stdio.h>
#include <stdbool.h>

#define MAXN 100  // 网格最大尺寸

// 网格：0 表示空地，1 表示障碍
int grid[MAXN][MAXN];
bool visited[MAXN][MAXN];

// 方向数组：上、下、左、右
int dx[4] = {-1, 1, 0, 0};//行号怎么变化
int dy[4] = {0, 0, -1, 1};//列号怎么变化

int rows, cols;  

//广度优先搜索
//队列节点：保存坐标和当前步数
typedef struct {
    int x, y;
    int step;  //从起点走到这里的步数
} Node;

typedef struct {
    Node data[MAXN * MAXN];
    int front, rear;
} Queue;

void InitQueue(Queue *Q) {
    Q->front = Q->rear = 0;
}

bool QueueEmpty(Queue *Q) {
    return Q->front == Q->rear;
}

void EnQueue(Queue *Q, Node n) {
    Q->data[Q->rear++] = n;
}

Node DeQueue(Queue *Q) {
    return Q->data[Q->front++];
}

// 从 (sx, sy) 到 (ex, ey) 的最短路径长度
int BFS_ShortestPath(int sx, int sy, int ex, int ey) {
    Queue Q;
    InitQueue(&Q);

    // 起点入队
    Node start = {sx, sy, 0};
    EnQueue(&Q, start);
    visited[sx][sy] = true;

    while (!QueueEmpty(&Q)) {
        Node cur = DeQueue(&Q);

        // 到达终点，返回步数（BFS 保证第一次到达就是最短）
        if (cur.x == ex && cur.y == ey) {
            return cur.step;
        }

        // 尝试向四个方向走
        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            // 边界判断、障碍判断、是否已访问
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] == 0 && !visited[nx][ny]) {
                visited[nx][ny] = true;
                Node next = {nx, ny, cur.step + 1};
                EnQueue(&Q, next);
            }
        }
    }

    return -1; // 无法到达
}



//深度优先搜素dfs
//全局变量记录当前找到的最短路径
int minSteps = 1e9;

// 从 (x, y) 走到 (ex, ey)，当前已经走了 step 步
void DFS(int x, int y, int ex, int ey, int step) {
    // 剪枝：已经比当前最优解还长，没必要继续
    if (step >= minSteps) return;

    // 到达终点，更新最优解
    if (x == ex && y == ey) {
        if (step < minSteps) minSteps = step;
        return;
    }

    // 尝试四个方向
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] == 0 && !visited[nx][ny]) {
            visited[nx][ny] = true;
            DFS(nx, ny, ex, ey, step + 1);
            visited[nx][ny] = false;  // 回溯，恢复现场
        }
    }
}


//// 从 (x, y) 出发，能不能走到 (ex, ey)
bool DFS(int x, int y, int ex, int ey) {
    // 到达终点
    if (x == ex && y == ey) return true;

    visited[x][y] = true;

    // 尝试四个方向
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols
            && grid[nx][ny] == 0 && !visited[nx][ny]) {
            if (DFS(nx, ny, ex, ey)) {
                return true;  // 找到一条路就返回
            }
        }
    }

    return false;  // 四个方向都走不通
}