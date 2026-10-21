#include <stdio.h>
#include <stdlib.h>

// 定义任务结构体
typedef struct {
    int start;
    int end;
    int duration;
} Task;

// 按照结束时间升序排序
int compareTasks(const void* a, const void* b) {
    Task* t1 = (Task*)a;
    Task* t2 = (Task*)b;
    if(t1->end!=t2->end){
        return t1->end - t2->end;
    }
    return t1->start - t2->start;
}

// 假设最大时间片不超过 2000000
#define MAX_TIME 2000005
int used[MAX_TIME]; 

int main() {
    Task tasks[100005];
    int n = 0;
    int s, e, d;
    
    while (scanf("%d %d %d", &s, &e, &d) != EOF) {
        tasks[n].start = s;
        tasks[n].end = e;
        tasks[n].duration = d;
        n++;
    }
    
    if (n == 0) {
        printf("0\n");
        return 0;
    }
    
    qsort(tasks, n, sizeof(Task), compareTasks);
    
    int ans = 0; 
    
    // 2. 遍历每个任务
    for (int i = 0; i < n; i++) {
        int l = tasks[i].start;
        int r = tasks[i].end;
        int need = tasks[i].duration;
        
        
        int cnt = 0;
        for (int t = l; t <= r; t++) {
            if (used[t] == 1) {
                cnt++;
            }
        }
        
        if (cnt >= need) {
            continue;
        }
        

        int diff = need - cnt;
        
        // 从右往左找空闲时间片填补
        for (int t = r; t >= l && diff > 0; t--) {
            if (used[t] == 0) { // 发现空闲时间片
                used[t] = 1;    // 标记为占用
                ans++;          // 电脑运行时间 +1
                diff--;         // 缺口减少 1
            }
        }
    }
    
    printf("%d\n", ans);
    return 0;
}