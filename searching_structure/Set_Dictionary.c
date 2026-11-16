//集合结构
//集合 和 字典(字典是一个集合)

//顺序搜索 遍历顺序表O(n)      想变成O(logn)或是O(1)
Contains(key)  Get(key)

//二分搜索 跳表 (利用堆排序O(nlongn) 建立有序数组/链表)
bool BinarySearch(int *A,int l,int r,int x){
    int m=(l+r)/2;//不用除法，则用斐波那契数列
    int mval=A[m];
    if(mval==x){
        return true;
    }
    else if(x<mval && l<=m-1){
        return BinarySearch(A,l,m-1,x);
    }
    else if(x>mval && r>=m+1){
        return BinarySearch(A,m+1,r,x);
    }
    return false;
}

//二叉搜索树
//搜索
TreeNode* Search(TreeNode* N,int x){//O(h)
    if(!N){
        return NULL;
    }
    if(N->val==x){
        return N;
    }
    if(N->val<x){
        return Search(N->right,x);
    }
    if(N->val>x){
        return Search(N->left,x);
    }
}

//插入
TreeNode* Insert(TreeNode* N,TreeNode* new){//O(h)
    if(!N){
        return new;
    }
    if(N->val==new->val){
        return N;
    }
    if(N->val<new->val){
        N->right=Insert(N->right,new);//得更新N->right 
        return N;
    }
    if(N->val>new->val){
        N->left=Insert(N->left,new);
        return N;
    }
}

//删除
/*1.叶节点，直接删除
2.右子树为空，以左子树填补
3.左子树为空，以右子树填补
4.左右都不为空，以右子树中序遍历第一节点替补，再删除原替补节点
*/
TreeNode* FindMin(TreeNode* Root) {
    while (Root->left != NULL) {
        Root = Root->left;
    }
    return Root;
}
TreeNode *Delete(TreeNode *Root, TreeNode *N) {//O(h)
    if (!Root) return NULL;
    if (N->val < Root->val)
        Root->left = Delete(Root->left, N);
    else if (N->val > Root->val)
        Root->right = Delete(Root->right, N);
    else {
        if (!Root->right) return Root->left;
        if (!Root->left) return Root->right;
        TreeNode* S = FindMin(Root->right);//find the left-most node, say S, of right tree
        Root->val = S.val;
        Root->right = Delete(Root->right, S);
    }
    return Root;//返回更新后的当前子树根
}

 
//AVL树
//从空树开始插入新节点，采用平衡旋转技术(左左，右右，左右，右左)

//插入  1-2次旋转
TreeNode : left val height right //(height也可以改成平衡因子/高度差 0 -1 1)
TreeNode *Insert(TreeNode *N, TreeNode *New) {
    if (!N) return New;
    if (N->val == New->val) return N;
    if (New->val < N->val)
        N->left = Insert(N->left, New);
    else N->right = Insert(N->right, New);
    return rebalance(N);//更新高度1+ max(left,right)，并据高度差进行旋转
}

//删除  O(logn)次旋转
TreeNode *Delete(TreeNode *Root, TreeNode *N) {
    if (!Root) return NULL;
    if (N->key < Root->key)
        Root->left = Delete(Root->left, N);
    else if (N->key > Root->key)
        Root->right = Delete(Root->right, N);
    else {
        if (!Root->right) return Root->left;
        if (!Root->left) return Root->right;
        TreeNode* S = FindMin(Root->right);//find the left-most node, say S, of right tree
        Root.key = S.key;
        Root.right = Delete(Root->right, S);
    }
    return rebalance(Root);//更新高度1+ max(left,right)，并据高度差进行旋转
}

//rebalance函数
int Height(TreeNode* Root) {
    if (Root == NULL)
        return 0;
    return Root->height;
}

int max(int a, int b) {
    return a > b ? a : b;
}
void UpdateHeight(TreeNode* Root) {
    Root->height = 1 + max(
        Height(Root->left),
        Height(Root->right)
    );
}

int BalanceFactor(TreeNode* Root) {
    if (Root == NULL)
        return 0;

    return Height(Root->left) - Height(Root->right);
}

TreeNode* RightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    UpdateHeight(y);
    UpdateHeight(x);

    return x;
}

TreeNode* LeftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    UpdateHeight(x);
    UpdateHeight(y);

    return y;
}

TreeNode* rebalance(TreeNode* Root) {
    if (Root == NULL)
        return NULL;
    // 1. 更新当前节点高度
    UpdateHeight(Root);
    // 2. 计算平衡因子
    int bf = BalanceFactor(Root);
    // 3. LL 或 LR 型
    if (bf > 1) {
        // LR 型：先左旋，再右旋
        if (BalanceFactor(Root->left) < 0)
            Root->left = LeftRotate(Root->left);
        // LL 型：右旋
        return RightRotate(Root);
    }
    // 4. RR 或 RL 型
    if (bf < -1) {
        // RL 型：先右旋，再左旋
        if (BalanceFactor(Root->right) > 0)
            Root->right = RightRotate(Root->right);
        // RR 型：左旋
        return LeftRotate(Root);
    }
    // 5. 已经平衡，不需要旋转
    return Root;
}