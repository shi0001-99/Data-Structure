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
strcpy(s1,s2)//
strchr(s,c)
strstr(s1,s2)//返回s2在s1第一次出现的位置指针

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