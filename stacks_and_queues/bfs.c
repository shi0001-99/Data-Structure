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