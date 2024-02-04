#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int maxn = 205;
int n, m, v[maxn], dp[maxn][maxn];
vector<int> ve[maxn];
int dfs(int u, int m)
{
    dp[u][1] = v[u];
    int sizeu = 1, sizev = 0;
    for (int i = 0; i < ve[u].size(); i++)
    {
        int v = ve[u][i];
        sizev = dfs(v, m-1);
        for (int j = m; j >= 1; j--)
        {
            for (int k = 1; k < min(sizev+1, j); k++)
            {
                dp[u][j] = max(dp[u][j], dp[v][k] + dp[u][j-k]);
            }
        }
        sizeu += sizev;
    }
    return sizeu;
}
int main()
{
    int a;
    while (scanf("%d%d", &n, &m))
    {
        if (n == 0 && m == 0) break;
        for (int i = 0; i <= n; i++) ve[i].clear();
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d", &a, &v[i]);
            ve[a].push_back(i);
        }
        // 增加超根
        m++, v[0] = 0;
        dfs(0, m);
        printf("%d\n", dp[0][m]);
    }
    return 0;
}