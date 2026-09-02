/*读入一组整数类型数据，判断其是等差数列还是等比数列
• 若是等差数列，输出公差
• 若是等比数列，输出公比
• 若既是等差又是等比数列，输出公差
• 若两者都不是，输出-1
公差公比皆为整数。
输入4 5
1 2 3 4 5
2 2 2 2 2 
1 2 4 8 16
1 2 3 4 8
输出1
0
2
-1
*/
#include <stdio.h>
int main()
{
    int x, y;
    scanf("%d %d", &x, &y);

    for (int row = 0; row < x; row++)
    {
        int arr[1000];
        for (int i = 0; i < y; i++)
        {
            scanf("%d", &arr[i]);
        }
        int ischa = 1;//状态标识，如果是等差的话设为1
        int diff = arr[1] - arr[0];
        for (int i = 2; i < y; i++)
        {
            if (arr[i] - arr[i - 1] != diff)
            {
                ischa = 0;
                break;
            }
        }
        int isbi = 1;//状态标识，如果是等比的话设为1
        int ratio;
        ratio = arr[1] / arr[0];
        for (int i = 2; i < y; i++)
        {
            if (arr[i]!=arr[i - 1] *ratio)//涉及到除法最好用乘法，避免整除
            {
                isbi = 0;
                break;
            }
        }
        if (ischa)
        {
            
            printf("%d\n", diff);
        }
        else if (isbi)
        {
            printf("%d\n", ratio);
        }
        else
        {
            printf("-1\n");
        }
    }
    return 0;
}