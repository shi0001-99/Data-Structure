typedef struct{
    int i,j;      //行，列
    ElmtType e;   //值
}Triple;

typedef struct{
    Triple data[MAXSIZE];  //三元组表
    int nrow,ncol,nelmt;   //矩阵的行数，列数，非零元素个数
}Matrix;

//常见的矩阵转置算法
for(int i=0;i<nrow;i++){
    for(int j=0;j<ncol;j++){
        T[j][i]=M[i][j];
    }
}

//三元组表示法
void Transpose(Matrix *M,Matrix *T){
    int p=0,q=0;//分别是M,T的位置
    for(col=0;col<M.col;col++){
        for(int p=0;p<M.elmt;p++){
            if(M.data[p].j==col){
                T.data[q].i=M.data[p].j;
                T.data[q].j=M.data[p].i;
                T.data[q].e=M.data[p].e;
                q++;
            }
        }
    }
}

//插入法
int num[col]; //正确的应该是指针变量，然后malloc开辟空间
for(int p=0;p<M.nelmt;p++){
    num[M.data[p].j]++;
}
int Loc[col];
Loc[0]=0;
for(int col=1;col<M.col;col++){
    Loc[col]=Loc[col-1]+num[col-1];
}

for(p=0;p<M.nelmt;p++){
    col=M.data[p].j;
    q=Loc[col];
    //Move M.data[p] to T.data[j]
    Loc[col]++;
}

//三元组的优化
typedef struct{
    Triple data[MAXSIZE];
    int nrow,ncol,nelmt;
    int rpos[MAXSIZE];//各行第一个非零元的位置，这样想找到某个元素就不需要从头遍历了
}

ElmtType value(Matrix M, int r, int c) {
    p = M.rpos[r];
    while (M.data[p].i == r && M.data[p].j < c) 
        p++;
    // j >= c
    if (M.data[p].i == r && M.data[p].j == c)
        return M.data[p].e;
    else
        return 0;
}

//十字链表表示法
typedef struct{
    int i,j;
    ElmtType e;
    struct Node* right;
    struct Node* down;
}Node;
typedef struct{
    Node **rhead,**chead;//指向指针数组的指针，rhead存的是指针数组头元素的地址
    int nrow,ncol,nelmt;
}Matrix;

// 行头指针数组：nrow 个
M->rhead = (Node**)malloc(nrow * sizeof(Node*));
// 列头指针数组：ncol 个
M->chead = (Node**)malloc(ncol * sizeof(Node*));