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

