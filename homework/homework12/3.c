#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int keynum;
    int leaf;                   // 1表示叶节点，0表示非叶节点
    int key[5];                 // 暂时允许存4个关键字
    struct TreeNode *ptr[5];    // 暂时允许4个孩子
    struct TreeNode *parent;
} TreeNode;

/* 创建节点 */
TreeNode *createNode(int leaf) {
    TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));

    p->keynum = 0;
    p->leaf = leaf;
    p->parent = NULL;

    for (int i = 0; i < 5; i++) {
        p->key[i] = 0;
        p->ptr[i] = NULL;
    }

    return p;
}

/* 返回节点所在子树的最大编号 */
int maxKey(TreeNode *p) {
    if (p == NULL || p->keynum == 0)
        return 0;

    return p->key[p->keynum];
}

/* 更新非叶节点的索引 */
void updateKeys(TreeNode *p) {
    if (p == NULL || p->leaf)
        return;

    for (int i = 1; i <= p->keynum; i++)
        p->key[i] = maxKey(p->ptr[i]);
}

/* 查找编号是否存在 */
int search(TreeNode *p, int x) {
    if (p == NULL)
        return 0;

    if (p->leaf) {
        for (int i = 1; i <= p->keynum; i++) {
            if (p->key[i] == x)
                return 1;
        }
        return 0;
    }

    int i = 1;

    while (i < p->keynum && x > p->key[i])
        i++;

    return search(p->ptr[i], x);
}

/* 叶节点插入关键字 */
void insertKey(TreeNode *p, int x) {
    int i = p->keynum;

    while (i >= 1 && p->key[i] > x) {
        p->key[i + 1] = p->key[i];
        i--;
    }

    p->key[i + 1] = x;
    p->keynum++;
}

/* 分裂叶节点 */
TreeNode *splitLeaf(TreeNode *p) {
    TreeNode *r = createNode(1);

    /* 前两个留在左节点 */
    p->keynum = 2;

    /* 后两个放入右节点 */
    r->key[1] = p->key[3];
    r->key[2] = p->key[4];
    r->keynum = 2;

    return r;
}

/* 分裂非叶节点 */
TreeNode *splitInternal(TreeNode *p) {
    TreeNode *r = createNode(0);

    /* 左节点保留前两个孩子 */
    p->keynum = 2;

    /* 右节点保留后两个孩子 */
    r->ptr[1] = p->ptr[3];
    r->ptr[2] = p->ptr[4];
    r->keynum = 2;

    /* 修改转移孩子的父节点 */
    r->ptr[1]->parent = r;
    r->ptr[2]->parent = r;

    /* 清除左节点中已转移的指针 */
    p->ptr[3] = NULL;
    p->ptr[4] = NULL;

    /* 更新左右节点的索引 */
    updateKeys(p);
    updateKeys(r);

    return r;
}

/* 递归插入，返回分裂产生的右节点 */
TreeNode *insert(TreeNode *p, int x) {
    /* 当前节点是叶节点 */
    if (p->leaf) {
        insertKey(p, x);

        /* 没有超过3个关键字 */
        if (p->keynum <= 3)
            return NULL;

        /* 叶节点分裂 */
        return splitLeaf(p);
    }

    /* 找到应该插入的孩子 */
    int i = 1;

    while (i < p->keynum && x > p->key[i])
        i++;

    /* 递归插入孩子 */
    TreeNode *r = insert(p->ptr[i], x);

    /* 子节点没有分裂 */
    if (r == NULL) {
        updateKeys(p);
        return NULL;
    }

    /* 子节点分裂，插入新右节点 */
    int pos = i + 1;

    for (int j = p->keynum; j >= pos; j--)
        p->ptr[j + 1] = p->ptr[j];

    p->ptr[pos] = r;
    r->parent = p;
    p->keynum++;

    /* 更新索引 */
    updateKeys(p);

    /* 当前节点未超过3个孩子 */
    if (p->keynum <= 3)
        return NULL;

    /* 非叶节点分裂 */
    return splitInternal(p);
}

/* 层序遍历输出 */
void levelOrder(TreeNode *root, int n) {
    if (root == NULL) {
        printf("0\n");
        return;
    }

    TreeNode **queue = (TreeNode **)malloc(
        (2 * n + 5) * sizeof(TreeNode *)
    );

    int front = 0, rear = 0;
    int count = 0;

    queue[rear++] = root;

    /* 统计节点数量 */
    while (front < rear) {
        TreeNode *p = queue[front++];
        count++;

        if (!p->leaf) {
            for (int i = 1; i <= p->keynum; i++)
                queue[rear++] = p->ptr[i];
        }
    }

    printf("%d\n", count);

    /* 重新开始层序遍历 */
    front = 0;
    rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        TreeNode *p = queue[front++];

        printf("%d", p->keynum);

        for (int i = 1; i <= p->keynum; i++)
            printf(" %d", p->key[i]);

        printf("\n");

        if (!p->leaf) {
            for (int i = 1; i <= p->keynum; i++)
                queue[rear++] = p->ptr[i];
        }
    }

    free(queue);
}

/* 主函数 */
int main() {
    int n;
    scanf("%d", &n);

    TreeNode *root = NULL;

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);

        /* 忽略重复编号 */
        if (search(root, x))
            continue;

        /* 空树 */
        if (root == NULL) {
            root = createNode(1);
            root->key[1] = x;
            root->keynum = 1;
        }
        else {
            TreeNode *r = insert(root, x);

            /* 根节点发生分裂 */
            if (r != NULL) {
                TreeNode *newRoot = createNode(0);

                newRoot->ptr[1] = root;
                newRoot->ptr[2] = r;
                newRoot->keynum = 2;

                root->parent = newRoot;
                r->parent = newRoot;

                updateKeys(newRoot);

                root = newRoot;
            }
        }
    }

    levelOrder(root, n);

    return 0;
}