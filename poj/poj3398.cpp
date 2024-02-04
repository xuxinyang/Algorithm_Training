#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
const int maxn = 1e4+5;
int n, dp[maxn][3];
// dp[u][0]表示u是服务器，其子节点是或不是服务器的最小服务器之和，最后再加上u节点是服务器的个数
// dp[u][1]表示u不是服务器，u的父节点是服务器，求所有子树的最小服务器数之和
// dp[u][2]表示u不是服务器，u的父亲也不是服务器的情况，则u恰好有一个子节点是服务器
vector<int> ve[maxn];

void dfs(int u, int fa)
{
    dp[u][0] = 1, dp[u][1] = 0, dp[u][2] = n;
    int k = ve[u].size();
    for (int i = 0; i < k; i++)
    {
        int v = ve[u][i];
        if (v == fa) continue;
        dfs(v, u);
        // 第一种情况
        dp[u][0] += min(dp[v][0], dp[v][1]);
        // 第二种情况
        dp[u][1] += dp[v][2];
    }
    for (int i = 0; i < k; i++)
    {
        // 第三种情况
        int v = ve[u][i];
        if (v == fa) continue;
        dp[u][2] = min(dp[u][2], dp[u][1] - dp[v][2] + dp[v][0]);
    }
}

int main()
{
    int u, v;
    while (~scanf("%d", &n))
    {
        for (int i = 1; i <= n; i++) ve[i].clear();
        for (int i = 1; i < n; i++)
        {
            scanf("%d%d", &u, &v);
            ve[u].push_back(v);
            ve[v].push_back(u);
        }
        dfs(1, 0);
        printf("%d\n", min(dp[1][0], dp[1][2]));
        scanf("%d", &u);
        if (u == -1) break;
    }
}