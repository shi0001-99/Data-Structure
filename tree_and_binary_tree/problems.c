//算树中的最长路径
#include <stdio.h>
#include <stdlib.h>

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

//---------------------------------------------------------
//算最长交错路径长度
#include <stdio.h>
#include <stdlib.h>

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


//-----------------------------------------------------------
//选与不选问题，求最少选多少节点使得所有边被覆盖
void dfs(Node* root, int* dp0, int* dp1) {
    if (!root) {
        *dp0 = 0;
        *dp1 = 0;
        return;
    }
    int l0, l1, r0, r1;
    dfs(root->left, &l0, &l1);
    dfs(root->right, &r0, &r1);
    *dp0 = l1 + r1;
    *dp1 = 1 + min(l0, l1) + min(r0, r1);
}

int cover_edges(Node *root) {
    int dp0, dp1;
    dfs(root, &dp0, &dp1);
    return min(dp0, dp1);
}

//-----------------------------------------------------------
//摄像头监控问题

int min(int a, int b) {
    return (a < b) ? a : b;
}

void dfs(struct TreeNode* root, int* need, int* safe, int* put) {
    if (!root) {
        *need = 0;
        *safe = 0;
        *put = 100000;//空节点不能安装摄像头
        return;
    }

    int l_need, l_safe, l_put;
    int r_need, r_safe, r_put;

    // 后序遍历
    dfs(root->left, &l_need, &l_safe, &l_put);
    dfs(root->right, &r_need, &r_safe, &r_put);

    // 状态一：当前节点安装摄像头，左右孩子无所谓什么状态
    *put = 1 + min(l_need, min(l_safe, l_put)) + min(r_need, min(r_safe, r_put));

    // 状态二：当前节点被孩子的摄像头监控，可以一边选一边不选，但是剩下的一边不能是need状态，因为当前节点没有摄像头
    int case_a = l_put + min(r_safe, r_put);
    int case_b = r_put + min(l_safe, l_put);
    *safe = min(case_a, case_b);

    // 状态三：当前节点需要父节点的摄像头监控，子节点都没有摄像头，且不是need状态，只能是safe状态
    *need = l_safe + r_safe;
}

int minCameraCover(struct TreeNode* root) {
    int root_need, root_safe, root_put;
    dfs(root, &root_need, &root_safe, &root_put);
    // 根节点没有父节点，因此不能处于 need 状态
    return min(root_safe, root_put);
}

//-----------------------------------------------------------
//把val替换成堂兄弟们的和
void Q2(TreeNode* root) {
    if (root == NULL) return;

    queue<TreeNode*> q;
    vector<int> sum, cnt;

    q.push(root);

    // 第一次层序遍历：求每层结点值之和、结点个数
    while (!q.empty()) {
        int n = q.size();
        int s = 0;

        for (int i = 0; i < n; i++) {
            TreeNode* p = q.front();
            q.pop();

            s += p->val;

            if (p->left)
                q.push(p->left);
            if (p->right)
                q.push(p->right);
        }

        sum.push_back(s);
        cnt.push_back(n);
    }

    // 第二次层序遍历：修改结点值
    q.push(root);
    int level = 0;

    while (!q.empty()) {
        int n = q.size();

        for (int i = 0; i < n; i++) {
            TreeNode* p = q.front();
            q.pop();

            int t = 0, k = 0;

            if (p->left) {
                t += p->left->val;
                k++;
            }

            if (p->right) {
                t += p->right->val;
                k++;
            }

            // 存在下一层，且孩子有堂兄弟
            if (level + 1 < cnt.size() &&
                cnt[level + 1] > k) {

                if (p->left)
                    p->left->val = sum[level + 1] - t;

                if (p->right)
                    p->right->val = sum[level + 1] - t;
            }

            if (p->left)
                q.push(p->left);
            if (p->right)
                q.push(p->right);
        }

        level++;
    }
}
