#include <stdio.h>
#include <stdlib.h>

#define m 3

typedef int KeyType;



typedef struct TreeNode {
    int keynum;                  // 节点中关键字个数
    struct TreeNode *parent;      // 双亲节点
    KeyType key[m + 1];           // 关键字，0号单元不用
    struct TreeNode *ptr[m + 1];  // 子树指针
} TreeNode;

/* 创建节点 */
TreeNode *createNode() {
    TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));

    p->keynum = 0;
    p->parent = NULL;

    for (int i = 0; i <= m; i++) {
        p->ptr[i] = NULL;

    }
    return p;
}

/* 查找关键字是否存在 */
int search(TreeNode *p, int x) {
    if (p == NULL)
        return 0;

    int i = 1;

    while (i <= p->keynum && x > p->key[i])
        i++;

    if (i <= p->keynum && x == p->key[i])
        return 1;

    return search(p->ptr[i - 1], x);
}

/* 
   将关键字x插入节点p的第pos个位置
   pos从1开始
*/
void insertKey(TreeNode *p, int pos, int x) {
    for (int i = p->keynum; i >= pos; i--)
        p->key[i + 1] = p->key[i];

    p->key[pos] = x;
    p->keynum++;
}

/* 
   将节点p分裂
   p中暂时有3个关键字

   key[2]向上提升
   左节点保留key[1]
   右节点保留key[3]
*/
void splitNode(TreeNode *p, int *promote, TreeNode **right) {
    TreeNode *r = createNode();

    *promote = p->key[2];

    // 左节点
    p->keynum = 1;

    // 右节点
    r->key[1] = p->key[3];
    r->keynum = 1;

    // 转移右侧子树
    r->ptr[0] = p->ptr[2];
    r->ptr[1] = p->ptr[3];

    if (r->ptr[0] != NULL)
        r->ptr[0]->parent = r;

    if (r->ptr[1] != NULL)
        r->ptr[1]->parent = r;

    // 清除左节点中已转移的指针
    p->ptr[2] = NULL;
    p->ptr[3] = NULL;

    *right = r;
}

/*
   递归插入

   返回1：当前节点发生分裂
   返回0：当前节点没有分裂

   promote：向上提升的关键字
   right：分裂产生的右节点
*/
int insert(TreeNode *p, int x, int *promote, TreeNode **right) {
    int i = 1;

    // 确定关键字插入位置
    while (i <= p->keynum && x > p->key[i])
        i++;

    // 如果是叶节点
    if (p->ptr[0] == NULL) {
        insertKey(p, i, x);
    }
    else {
        // 进入对应子树
        int mid;
        TreeNode *newRight = NULL;

        int split = insert(p->ptr[i - 1], x, &mid, &newRight);

        // 子节点没有分裂
        if (!split)
            return 0;

        // 子节点分裂，将关键字插入当前节点
        insertKey(p, i, mid);

        // 调整子树指针
        for (int j = p->keynum; j >= i + 1; j--)
            p->ptr[j] = p->ptr[j - 1];

        p->ptr[i] = newRight;

        newRight->parent = p;
    }

    // 当前节点未超过容量
    if (p->keynum <= 2)
        return 0;

    // 当前节点超过容量，分裂
    splitNode(p, promote, right);

    return 1;
}

/* 层序遍历 */
void levelOrder(TreeNode *root, int n) {
    if (root == NULL) {
        printf("0\n");
        return;
    }

    TreeNode **queue = (TreeNode **)malloc((n + 1) * sizeof(TreeNode *));

    int front = 0, rear = 0;
    int count = 0;

    // 计算节点数量
    queue[rear++] = root;

    while (front < rear) {
        TreeNode *p = queue[front++];
        count++;

        for (int i = 0; i <= p->keynum; i++) {
            if (p->ptr[i] != NULL)
                queue[rear++] = p->ptr[i];
        }
    }

    // 输出节点总数
    printf("%d\n", count);

    // 重新进行层序遍历
    front = 0;
    rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        TreeNode *p = queue[front++];

        printf("%d", p->keynum);

        for (int i = 1; i <= p->keynum; i++)
            printf(" %d", p->key[i]);

        printf("\n");

        for (int i = 0; i <= p->keynum; i++) {
            if (p->ptr[i] != NULL)
                queue[rear++] = p->ptr[i];
        }
    }

    free(queue);
}

int main() {
    int n;
    scanf("%d", &n);

    TreeNode *root = NULL;

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);

        // 已存在的关键字不再插入
        if (search(root, x))
            continue;

        // 空树
        if (root == NULL) {
            root = createNode();
            root->key[1] = x;
            root->keynum = 1;
        }
        else {
            int promote;
            TreeNode *right = NULL;

            // 插入根节点，如果根分裂则建立新根
            if (insert(root, x, &promote, &right)) {
                TreeNode *newRoot = createNode();

                newRoot->key[1] = promote;
                newRoot->keynum = 1;

                newRoot->ptr[0] = root;
                newRoot->ptr[1] = right;

                root->parent = newRoot;
                right->parent = newRoot;

                root = newRoot;
            }
        }
    }

    levelOrder(root, n);

    return 0;
}