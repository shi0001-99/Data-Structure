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
TreeNode *Delete(TreeNode *Root, TreeNode *N) {//O(h)
    if (!Root) return NULL;
    if (N->key < Root->key)
        Root->left = Delete(Root->left, N);
    else if (N->key > Root->key)
        Root->right = Delete(Root->right, N);
    else {
        if (!Root->right) return Root->left;
        if (!Root->left) return Root->right;
        // .. find the left-most node, say S, of right tree
        Root->key = S.key;
        Root->right = Delete(Root->right, S);
    }
    return Root;//返回更新后的当前子树根
}

