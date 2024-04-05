#include <bits/stdc++.h>
using namespace std;
const int maxn = 505;
const int maxm = 505;
int t, n, m, dp[maxn][maxm], a[maxn] , b[maxm];
int solve()
{
    memset(dp, 0, sizeof(dp));
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int val = 0;
        for (int j = 1; j <= m; j++)
        {
            if (a[i] != b[j]) dp[i][j] = dp[i-1][j];
            else dp[i][j] = val + 1;
            if (b[j] < a[i]) val = max(val, dp[i-1][j]);
            ans = max(ans, dp[i][j]);
        }
    }
    return ans;
}
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        scanf("%d", &m);
        for (int i = 1; i <= m; i++) scanf("%d", &b[i]);
        printf("%d\n", solve());
    }
    return 0;
}