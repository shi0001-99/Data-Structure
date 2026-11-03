#include <stdio.h>
#include <stdlib.h>

// 假设 node 结构体已定义
typedef struct node {
    int val;
    struct node *leftchild, *rightchild;
} node;

// 宏定义：求两个数中的最大值
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// 全局变量，记录最大路径和（初始化为极小值）
int maxSum = -1000000; 

// 辅助函数：返回以 p 为起点的单边最大贡献值
int dfs(node* p) {
    // 空结点贡献为 0
    if (p == NULL) {
        return 0;
    }

    // 递归计算左右子树的单边最大贡献
    // 如果子树贡献为负，则不如不走（取 0）
    int leftGain = MAX(0, dfs(p->leftchild));
    int rightGain = MAX(0, dfs(p->rightchild));

    // 计算经过当前结点的完整路径和（左单边 + 当前 + 右单边）
    // 这个路径可能成为全局最优解
    int currentPathSum = p->val + leftGain + rightGain;
    if (currentPathSum > maxSum) {
        maxSum = currentPathSum;
    }

    // 返回当前结点能提供给父节点的“单边”最大贡献
    // 只能选左或右中较大的一个
    return p->val + MAX(leftGain, rightGain);
}

// 主函数
int maxPathSum(node* root) {
    maxSum = -1000000; // 重置全局变量
    dfs(root);
    return maxSum;
}



#include <stdio.h>
#include <stdlib.h>

// 假设结构体已经定义好
typedef struct node {
    int val;
    struct node *leftchild, *rightchild;
} node;

int maxLen = 0; // 全局变量记录最大长度

// 辅助函数：计算以 p 为起点的最长交错路径
// ret_left 返回第一步向左的最长路径，ret_right 返回第一步向右的最长路径
void dfs(node* p, int* ret_left, int* ret_right) {
    // 如果结点为空，路径长度为 0
    if (p == NULL) {
        *ret_left = 0;
        *ret_right = 0;
        return;
    }

    int left_go_left = 0, left_go_right = 0;
    int right_go_left = 0, right_go_right = 0;

    // 递归获取左孩子的状态
    dfs(p->leftchild, &left_go_left, &left_go_right);
    // 递归获取右孩子的状态
    dfs(p->rightchild, &right_go_left, &right_go_right);

    // 1. 计算当前结点第一步向左走的最大路径
    // 前提是有左孩子，且走到左孩子后，下一步必须向右走 (取 left_go_right)
    if (p->leftchild != NULL) {
        *ret_left = 1 + left_go_right;
    } else {
        *ret_left = 0;
    }

    // 2. 计算当前结点第一步向右走的最大路径
    // 前提是有右孩子，且走到右孩子后，下一步必须向左走 (取 right_go_left)
    if (p->rightchild != NULL) {
        *ret_right = 1 + right_go_left;
    } else {
        *ret_right = 0;
    }

    // 3. 更新全局最大值
    if (*ret_left > maxLen) maxLen = *ret_left;
    if (*ret_right > maxLen) maxLen = *ret_right;
}

// 主调用函数
int longestZigZag(node* root) {
    maxLen = 0; // 初始化全局变量
    if (root != NULL) {
        int dummy_left, dummy_right;
        dfs(root, &dummy_left, &dummy_right);
    }
    return maxLen;
}