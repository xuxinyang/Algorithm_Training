#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int inf = 0x3f3f3f3f;
double ans, dp[1<<10][32];  // dp[s][u]表示到达当前u节点（持有s的车票）的最小时间
int n, m, p, a, b;
int t[20], dis[50][50];
void solve()
{
    for (int i = 0; i < (1<<n); i++) fill(dp[i], dp[i]+m+1, inf);
    dp[(1<<n)-1][a] = 0;    // 起点
    ans = inf;
    for (int S = (1<<n)-1; S >= 0; S--)
    {
        for (int u = 1; u <= m; u++)    // 枚举城市
        {
            for (int i = 0; i < n; i++) // 枚举车票
                if ((S>>i)&1)   // 有第i张车票
                    for (int v = 1; v <= m; v++)    // 枚举到达城市
                        if (dis[u][v] >= 0) // 有路
                            // 求最小值
                            dp[S&~(1<<i)][v] = min(dp[S&~(1<<i)][v], dp[S][u] + dis[u][v]/(double)t[i]);
        }
        ans = min(ans, dp[S][b]);
    }
}
int main()
{
    while (~scanf("%d%d%d%d%d", &n, &m, &p, &a, &b))
    {
        if (n + m + p + a + b == 0) break;
        for (int i = 0; i < n; i++) scanf("%d", &t[i]);
        memset(dis, -1, sizeof(dis));
        for (int i = 0; i < p; i++)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            dis[u][v] = dis[v][u] = w;
        }
        solve();
        if (ans == inf) printf("Impossible\n");
        else printf("%.3lf\n", ans);
    }
    return 0;
}