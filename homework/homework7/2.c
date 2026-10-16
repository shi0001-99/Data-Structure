#include <stdio.h>
#include <string.h>
//输入aaaabbbcc   输出4a3b2c
int main() {
    char s[1000];
    scanf("%s", s);

    int n = strlen(s);

    char pre = s[0];        
    int prenum = 1;         

    for (int i = 1; i < n; i++) {
        if (s[i] == pre) {
            prenum++;       
        } else {
            if (prenum == 1) printf("%c", pre);
            else             printf("%d%c", prenum, pre);

            pre = s[i];
            prenum = 1;
        }
    }
    if (prenum == 1) printf("%c", pre);
    else             printf("%d%c", prenum, pre);

    return 0;
}