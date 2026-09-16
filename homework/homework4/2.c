#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int nums[4000000];   
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    
    for (int i = 0; i < n; i++) {
        
        while (nums[i] >= 1 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
            int tmp = nums[i];
            nums[i] = nums[tmp - 1];
            nums[tmp - 1] = tmp;
        }
    }

   
    for (int i = 0; i < n; i++) {
        if (nums[i] != i + 1) {
            printf("%d\n", i + 1);
            return 0;
        }
    }

    
    printf("%d\n", n + 1);
    return 0;
}