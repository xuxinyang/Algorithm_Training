#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int dp[105][105];
char s[105];
/**
 * @brief 判断括号是否匹配
 */
bool match(int l, int r)
{
    if (s[l] == '(' && s[r] == ')') return true;
    if (s[l] == '[' && s[r] == ']') return true;
    return false;
}
int main()
{
    while (~scanf("%s", s) && s[0] != 'e')
    {
        int n = strlen(s);
        memset(dp, 0, sizeof(dp));
        // 使用区间DP求解
        for (int d = 2; d <= n; d++)    // 外层循环枚举规模（区间长度）
        {
            for (int i = 0; i < n-d+1; i++) // 枚举区间起点
            {
                int j = i + d - 1;  // 区间终点
                if (match(i, j)) dp[i][j] = dp[i+1][j-1] + 2;
                for (int k = i; k < j; k++) // 枚举切割点(决策点)
                {
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k+1][j]);
                }
            }
        }
        printf("%d\n", dp[0][n-1]);
    }
    return 0;
}