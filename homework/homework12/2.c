#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int keynum;
    struct TreeNode *parent;
    int key[4];              // key[0]不用，最多暂时存3个关键字
    struct TreeNode *ptr[4];  // ptr[0]~ptr[3]
} TreeNode;

/* 创建节点 */
TreeNode *createNode() {
    TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));

    p->keynum = 0;
    p->parent = NULL;

    for (int i = 0; i < 4; i++) {
        p->key[i] = 0;
        p->ptr[i] = NULL;
    }

    return p;
}

/* 查找关键字 */
int search(TreeNode *p, int x) {
    if (p == NULL)
        return 0;

    int i = 1;

    while (i <= p->keynum && x > p->key[i])
        i++;

    if (i <= p->keynum && x == p->key[i])
        return 1;

    if (p->ptr[0] == NULL)
        return 0;

    return search(p->ptr[i - 1], x);
}

/* 在节点内部插入关键字 */
void insertKey(TreeNode *p, int pos, int x) {
    for (int i = p->keynum; i >= pos; i--)
        p->key[i + 1] = p->key[i];

    p->key[pos] = x;
    p->keynum++;
}

/* 在节点内部插入关键字及其右侧新子树 */
void insertPromoted(TreeNode *p, int pos, int x,
                    TreeNode *newRight) {
    for (int i = p->keynum; i >= pos; i--)
        p->key[i + 1] = p->key[i];

    for (int i = p->keynum; i >= pos; i--)
        p->ptr[i + 1] = p->ptr[i];

    p->key[pos] = x;
    p->ptr[pos] = newRight;
    p->keynum++;

    if (newRight != NULL)
        newRight->parent = p;
}

/* 节点分裂 */
void splitNode(TreeNode *p, int *promote, TreeNode **right) {
    TreeNode *r = createNode();

    *promote = p->key[2];

    /* 左节点保留第一个关键字 */
    p->keynum = 1;

    /* 右节点保留第三个关键字 */
    r->key[1] = p->key[3];
    r->keynum = 1;

    /* 转移右侧子树 */
    r->ptr[0] = p->ptr[2];
    r->ptr[1] = p->ptr[3];

    if (r->ptr[0] != NULL)
        r->ptr[0]->parent = r;

    if (r->ptr[1] != NULL)
        r->ptr[1]->parent = r;

    p->ptr[2] = NULL;
    p->ptr[3] = NULL;

    *right = r;
}

/* 递归插入 */
int insert(TreeNode *p, int x, int *promote,
           TreeNode **right) {
    int i = 1;

    while (i <= p->keynum && x > p->key[i])
        i++;

    /* 当前节点是叶节点 */
    if (p->ptr[0] == NULL) {
        insertKey(p, i, x);
    }
    else {
        int mid;
        TreeNode *newRight = NULL;

        int split = insert(p->ptr[i - 1], x,
                          &mid, &newRight);

        if (!split)
            return 0;

        /* 子节点分裂，插入提升的关键字 */
        insertPromoted(p, i, mid, newRight);
    }

    /* 当前节点未超过容量 */
    if (p->keynum <= 2)
        return 0;

    /* 当前节点分裂 */
    splitNode(p, promote, right);

    return 1;
}

/* 删除节点内部指定位置的关键字 */
void deleteKey(TreeNode *p, int pos) {
    for (int i = pos; i < p->keynum; i++)
        p->key[i] = p->key[i + 1];

    p->key[p->keynum] = 0;
    p->keynum--;
}

/* 删除父节点的一个关键字和一个子树指针 */
void removeParentKeyAndChild(TreeNode *p,
                             int keyPos,
                             int childPos) {
    int oldNum = p->keynum;

    /* 删除关键字 */
    for (int i = keyPos; i < oldNum; i++)
        p->key[i] = p->key[i + 1];

    p->key[oldNum] = 0;

    /* 删除子树指针 */
    for (int i = childPos; i < oldNum; i++)
        p->ptr[i] = p->ptr[i + 1];

    p->ptr[oldNum] = NULL;

    p->keynum--;
}

/* 解决节点关键字数量不足的问题 */
void fixUnderflow(TreeNode **root, TreeNode *p) {
    while (p != *root && p->keynum == 0) {
        TreeNode *parent = p->parent;

        /* 找到 p 在父节点中的子树位置 */
        int c = 0;

        while (c <= parent->keynum &&
               parent->ptr[c] != p)
            c++;

        TreeNode *left = (c > 0) ?
                         parent->ptr[c - 1] : NULL;

        TreeNode *right = (c < parent->keynum) ?
                          parent->ptr[c + 1] : NULL;

        /* 情况1：优先向左兄弟借 */
        if (left != NULL && left->keynum == 2) {
            /* 父节点分隔关键字下移 */
            p->key[1] = parent->key[c];
            p->keynum = 1;

            /* 左兄弟最大关键字上移 */
            parent->key[c] = left->key[2];
            left->key[2] = 0;
            left->keynum = 1;

            /* 转移子树 */
            p->ptr[1] = p->ptr[0];
            p->ptr[0] = left->ptr[2];
            left->ptr[2] = NULL;

            if (p->ptr[0] != NULL)
                p->ptr[0]->parent = p;

            return;
        }

        /* 情况2：向右兄弟借 */
        if (right != NULL && right->keynum == 2) {
            /* 父节点分隔关键字下移 */
            p->key[1] = parent->key[c + 1];
            p->keynum = 1;

            /* 右兄弟最小关键字上移 */
            parent->key[c + 1] = right->key[1];

            /* 转移子树 */
            p->ptr[1] = right->ptr[0];

            if (p->ptr[1] != NULL)
                p->ptr[1]->parent = p;

            /* 右兄弟关键字左移 */
            right->key[1] = right->key[2];
            right->key[2] = 0;
            right->keynum = 1;

            /* 右兄弟子树指针左移 */
            right->ptr[0] = right->ptr[1];
            right->ptr[1] = right->ptr[2];
            right->ptr[2] = NULL;

            return;
        }

        /* 情况3：左右兄弟都不能借，合并 */

        if (left != NULL) {
            /* 与左兄弟合并 */
            left->key[2] = parent->key[c];
            left->keynum = 2;

            /* 将 p 的子树接到左兄弟右侧 */
            left->ptr[2] = p->ptr[0];

            if (left->ptr[2] != NULL)
                left->ptr[2]->parent = left;

            /* 删除父节点分隔关键字和 p 指针 */
            removeParentKeyAndChild(parent, c, c);

            free(p);

            /* 父节点可能继续出现下溢 */
            p = parent;
        }
        else {
            /* 没有左兄弟，与右兄弟合并 */
            p->key[1] = parent->key[1];
            p->key[2] = right->key[1];
            p->keynum = 2;

            /* 合并子树指针 */
            p->ptr[1] = right->ptr[0];
            p->ptr[2] = right->ptr[1];

            if (p->ptr[1] != NULL)
                p->ptr[1]->parent = p;

            if (p->ptr[2] != NULL)
                p->ptr[2]->parent = p;

            /* 删除父节点分隔关键字和右兄弟指针 */
            removeParentKeyAndChild(parent, 1, 1);

            free(right);

            /* 父节点可能继续出现下溢 */
            p = parent;
        }    
    }

    /* 根节点调整 */
    if (*root != NULL && (*root)->keynum == 0) {
        TreeNode *oldRoot = *root;

        *root = oldRoot->ptr[0];

        if (*root != NULL)
            (*root)->parent = NULL;

        free(oldRoot);
    }
}

/* 删除关键字 */
void deleteNode(TreeNode **root, int x) {
    if (*root == NULL)
        return;

    TreeNode *p = *root;
    int pos = 1;

    /* 找到关键字所在节点 */
    while (p != NULL) {
        pos = 1;

        while (pos <= p->keynum && x > p->key[pos])
            pos++;

        if (pos <= p->keynum && x == p->key[pos])
            break;

        if (p->ptr[0] == NULL)
            return;

        p = p->ptr[pos - 1];
    }

    if (p == NULL)
        return;

    /* 如果是内部节点，找右子树最小关键字 */
    if (p->ptr[0] != NULL) {
        TreeNode *q = p->ptr[pos];

        while (q->ptr[0] != NULL)
            q = q->ptr[0];

        /* 用后继替换 x */
        p->key[pos] = q->key[1];

        /* 到后继所在叶节点删除 */
        p = q;
        pos = 1;
    }

    /* 删除叶节点中的关键字 */
    deleteKey(p, pos);

    /* 如果节点下溢，进行调整 */
    if (p->keynum == 0)
        fixUnderflow(root, p);
}

/* 层序遍历输出 */
void levelOrder(TreeNode *root, int n) {
    if (root == NULL) {
        printf("0\n");
        return;
    }

    TreeNode **queue = (TreeNode **)malloc(
        (n + 1) * sizeof(TreeNode *)
    );

    int front = 0, rear = 0;
    int count = 0;

    queue[rear++] = root;

    /* 统计节点数 */
    while (front < rear) {
        TreeNode *p = queue[front++];
        count++;

        for (int i = 0; i <= p->keynum; i++) {
            if (p->ptr[i] != NULL)
                queue[rear++] = p->ptr[i];
        }
    }

    printf("%d\n", count);

    /* 重新遍历输出节点 */
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

/* 根据输入的层序节点信息建立树 */
TreeNode *buildTree(int m) {
    if (m == 0)
        return NULL;

    TreeNode **nodes = (TreeNode **)malloc(m * sizeof(TreeNode *));

    /* 先创建所有节点并读取关键字 */
    for (int i = 0; i < m; i++) {
        nodes[i] = createNode();

        scanf("%d", &nodes[i]->keynum);

        for (int j = 1; j <= nodes[i]->keynum; j++)
            scanf("%d", &nodes[i]->key[j]);
    }

    /* 按层序输入顺序分配子树 */
    int next = 1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= nodes[i]->keynum; j++) {
            if (next >= m)
                break;

            nodes[i]->ptr[j] = nodes[next];
            nodes[next]->parent = nodes[i];
            next++;
        }
    }

    TreeNode *root = nodes[0];

    free(nodes);

    return root;
}

/* 主函数 */
int main() {
    int m;
    scanf("%d", &m);

    TreeNode *root = buildTree(m);

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        char op;
        int x;

        scanf(" %c %d", &op, &x);

        if (op == 'I') {
            /* 已存在则忽略 */
            if (search(root, x))
                continue;

            /* 树为空 */
            if (root == NULL) {
                root = createNode();
                root->key[1] = x;
                root->keynum = 1;
            }
            else {
                int promote;
                TreeNode *right = NULL;

                if (insert(root, x, &promote, &right)) {
                    /* 根节点分裂，创建新根 */
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
        else if (op == 'D') {
            deleteNode(&root, x);
        }
    }

    levelOrder(root, m + q);

    return 0;
}