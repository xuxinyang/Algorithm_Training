#include <bits/stdc++.h>
using namespace std;
int dp[20][2], a[20];
// dp[pos][sta]表示当前第pos位，sta状态下满足条件的个数，sta表示前一位是否是6，只有0和1两种状态
int dfs(int pos, bool sta, bool limit)
{
    if (pos == 0) return 1; // 走到叶子节点
    // 没有限制且解过了
    if (!limit && dp[pos][sta] != -1) return dp[pos][sta];
    int len = limit ? a[pos]:9;
    int ans = 0;
    for (int i = 0; i <= len; i++)
    {
        if (sta && i == 2) continue;    // 跳过62
        if (i == 4) continue;   // 4也跳过
        ans += dfs(pos-1, i==6, limit && i == len);
    }
    if (!limit) dp[pos][sta] = ans; // 无限制才可以记忆
    return ans;
} 
// 求解[0...x]之间满足条件的个数
int solve(int x)
{
    int pos = 0;
    while (x)
    {
        a[++pos] = x % 10;
        x /= 10;
    }
    return dfs(pos, 0, 1);  // 如果不包括0，此处减1即可
}
int main()
{
    int a, b;
    memset(dp, -1, sizeof(dp));
    while (~scanf("%d%d", &a, &b), a + b)
    {
        printf("%d\n", solve(b) - solve(a-1));
    }
    return 0;
}