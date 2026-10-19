typedef struct{
    char *ch;//串的顺序表，空串为NULL
    int length;//串的长度
}String;

char* ch;//串的顺序表，空串为NULL
         //'\0'标记末尾

#include<string.h>
strlen()//返回长度 O(n)
strcmp()//相同返回0，否则非0
strcat(s1,s2)//把s2放到s1的末尾,s1要有足够空间
strcpy(s1,s2)//把s2复制到s1,s1必须要有足够的空间
strchr(s,c)//返回c在s中第一次出现的位置指针
strstr(s1,s2)//返回s2在s1第一次出现的位置指针


//暴力枚举BF 时间复杂度O(m*n)
//法一
char* strstr(const char *s1, const char *s2) {
    int length1 = strlen(s1);
    int length2 = strlen(s2);

    if (length2 == 0) return (char*)s1;   // 空串返回 s1
    if (length1 < length2) return NULL;

    for (int i = 0; i <= length1 - length2; i++) {
        int j = 0;//偏移量
        while (j < length2 && s1[i + j] == s2[j]) {
            j++;
        }
        if (j == length2) {
            return (char*)(s1 + i);
        }
    }
    return NULL;
}

//法二
char* strstr(char* s,char* t){
    int n=strlen(s);
    int m=strlen(t);
    int i=0;//遍历s
    int j=0;//遍历t
    while(i<n && j<m){
        if(s[i]==t[j]){
            i++;
            j++;
        }
        else{
            i=i-j+1;
            j=0;
        }
    }
    if(j>=m){
        return s+i-j;
    }
    else{
        return NULL;
    }
}


//KMP算法  让i保持不后退 整体时间复杂度是O(m+n) 匹配阶段时间复杂度是O(n)
char *strstr(char *s,char *t,int *next){//假设next已经计算完毕
    int n=strlen(s);
    int m=strlen(t);
    int i=0;
    int j=0;
    while(i<n && j<m){
        if(s[i]==t[j]){
            i++;
            j++;
        }
        else if(j>0){
            j=next[j-1];
        }
        else{
            i++;
        }
    }
    if(j>=m){
        return s+i-j;
    }
    else{
        return NULL;
    }
}

//构建next的时间复杂度O(m)
char *build_next(char *T) {//寻找子串中的最长相同 真 前后缀的长度
    int m = strlen(T);
    int *Next =(int*)malloc(sizeof(int)*m); 
    Next[0] = 0;
    int prefix_length = 0;
    int i=1;
    while (i < m){
        if (T[i] == T[prefix_length]){
            Next[i++] = ++prefix_length;
        }
        else {
            if(prefix_length == 0){
                Next[i++] = 0;
                continue;
            }
            prefix_length = Next[prefix_length - 1];//在前后缀里面再找 最长相同真前后缀的长度
        }
    }
    return Next;
}


//最短与最长回文串
/*最短回文串：给定字符串 s，通过在其前面添加字符将其转换为回文串
             找到并返回可以得到的最短回文串
  输入"aacecaaa"  可以看成 aacecaa a,只需要把最后的a反转加到头部即可
  输出"aaacecaaa"

  先变成 aacecaaa#aaacecaa (s逆置)
  然后看拼接字符串next数组的最后一位
*/

/*最长回文串：给定串s，返回其中包含的（一条）最长回文子串
  输入"babad"
  输出"bab" 或者 "aba"

  法一：for(i=1..n): 以第i个字符为起始字符使用KMP，同上
  法二：for(i=1..n), 以i为中点，向两边展开寻找回文
        区分奇偶：奇数：单个遍历
                 偶数：以两个为一组
        插入 # 使奇偶统一
*/


//最长公共子序列
int sub(char* x,char* y){//时间复杂度O(n)
    int i=0;
    int j=0;
    int lx=strlen(x);
    int ly=strlen(y);
    while(i<lx && j<ly){
        if(x[i]==y[j]){
            i++;
            j++;
        }
        else{
            i++;
        }
    }
    if(j==ly){
        return 1;//成功
    }
    else{
        return 0;//失败
    }
}


