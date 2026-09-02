/*读入一组整数类型数据，找到并输出最大值及最小值。
  第一行给出数组长度；第二行给出数组
   输入6
   5 3 8 7 19 12
   输出19 3
*/
#include <stdio.h>
#include<stdlib.h> //有calloc...atoi...qsort...
int main()
{
    int n;
    scanf("%d", &n);
    int max, min, temp;
    scanf("%d", &temp);//先读取一个数
    max = temp;
    min = temp; //记录目前已有数组的最大值最小值
    for (int i = 1; i < n; i++) //读取剩下的n-1个数
    {
        scanf("%d", &temp);
        if (temp > max)
        {
            max = temp;
        }
        if (temp < min)
        {
            min = temp;
        }
    }
    printf("%d %d", max, min);
    return 0;
}