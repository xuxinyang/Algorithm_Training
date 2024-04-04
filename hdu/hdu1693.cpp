#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll dp[2][1<<12], ans;
int n, m, v;
void solve()
{
    int total = 1 << (m+1); // m+1位
    int pre = 0, now = 1;
    memset(dp[pre], 0, sizeof(dp[pre]));
    dp[pre][0] = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++){
            scanf("%d", &v);
            memset(dp[now], 0, sizeof(dp[now]));
            int j0 = 1 << j;    // j位为1，其他位为0
            int j1 = j0 << 1;   // j+1位为1，其它位为0
            for (int S = 0; S < total; S++)
            {
                bool p = S & j0, q = S & j1;    // 前一个格子的左，上状态
                if (v == 0) // 障碍物，走不通
                {
                    if (!p && !q) dp[now][S] += dp[pre][S];
                }
                else
                {
                    if (p ^ q) // 有一个为1，一个为0
                        dp[now][S] += dp[pre][S];   // 原状态不变
                    dp[now][S^j0^j1] += dp[pre][S]; // 相反状态
                }
            }
            swap(pre, now);
        }
        memset(dp[now], 0, sizeof(dp[now]));        // 换行，清零
        for (int S = 0; S < total / 2; S++) dp[now][S<<1] = dp[pre][S]; // S左移一位
        swap(pre, now);
    }
    ans = dp[now][0];
}
int main()
{
    int T, cas = 1;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        solve();
        printf("Case %d: There are %I64d ways to eat the trees.\n", cas++, ans);
    }
    return 0;
}