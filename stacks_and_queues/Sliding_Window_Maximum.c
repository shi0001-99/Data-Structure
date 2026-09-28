//时间复杂度O(n*k)
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main() {
    int n, k;
    scanf_s("%d%d", &n, &k);
    int arr[100];
    for (int i = 0; i < n; i++) {
        scanf_s("%d", &arr[i]);
    }
    int maxnum = -10000;
    
    for (int i = 0; i < n - k + 1; i++) {
        for (int j = i; j < i + k; j++) {
            if (maxnum < arr[j]) {
                maxnum = j;
            }
        }
    }
    printf("%d", maxnum);
    return 0;
}

//时间复杂度O(n)
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main(){
    int n, k;
    scanf_s("%d%d", &n, &k);
}