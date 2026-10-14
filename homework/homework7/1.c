#include <stdio.h>
#include <string.h>

int a[5005], b[5005];      
int tmp[2000005];          

int main() {
    int n, x;
    scanf("%d", &n);
    scanf("%d", &x);

    int la = 0, lb = 0;
    for (int i = 0; i < n; i++) {
        int v;
        scanf("%d", &v);
        if (v < x) a[la++] = v ;
        else       b[lb++] = v ;
    }

    if (la == 0 || lb == 0) {
        printf("0\n");
        return 0;
    }

    for (int i = la - 1; i >= 0; i--) {
        for (int j = lb - 1; j >= 0; j--) {
            int mul = (a[i]) * (b[j]);
            int p1 = i + j;
            int p2 = i + j + 1;
            int sum = mul + tmp[p2];
            tmp[p2] = sum % 10;
            tmp[p1] += sum / 10;
        }
    }

    
    for (int i = la + lb - 1; i > 0; i--) {
        tmp[i - 1] += tmp[i] / 10;
        tmp[i] %= 10;
    }

  
    int k = 0;
    while (k < la + lb - 1 && tmp[k] == 0) k++;

  
    for (; k < la + lb; k++) {
        printf("%d", tmp[k]);
    }
    printf("\n");

    return 0;
}