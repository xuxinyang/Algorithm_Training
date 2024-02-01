#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;
const int maxn = 1e3+5;
const int inf = 0x3f3f3f3f;
int dp[maxn<<1][maxn<<1], s[maxn<<1][maxn<<1], sum[maxn<<1];
int n, a[maxn<<1];
void init()
{
    sum[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        sum[i] = sum[i-1] + a[i];
        dp[i][i] = 0;
        s[i][i] = i;    // 最优决策点
    }
    for (int i = 1; i < n; i++)
    {
        a[n+i] = a[i];
        sum[n+i] = a[n+i] + sum[n+i-1];
        dp[n+i][n+i] = 0;
        s[n+i][n+i] = n + i;
    }
}
void solve()
{
    for (int d = 2; d <= n; d++)
    {
        for (int i = 1; i <= 2 * n - d; i++)
        {
            int j = i + d - 1;
            // 枚举k值求最小值
            int tmp = sum[j] - sum[i-1];
            dp[i][j] = inf;
            for (int k = s[i][j-1]; k <= s[i+1][j]; k++)
            {
                if (dp[i][j] > dp[i][k] + dp[k+1][j] + tmp)
                {
                    dp[i][j] = dp[i][k] + dp[k+1][j] + tmp;
                    s[i][j] = k;
                }
            }
        }
    }
    int ans = inf;
    for (int i = 1; i <= n; i++)
        ans = min(ans, dp[i][n+i-1]);
    printf("%d\n", ans);
}
int main()
{
    while (~scanf("%d", &n))
    {
        init();
        solve();
    }
    return 0;
}