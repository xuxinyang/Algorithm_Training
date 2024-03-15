#include <cstring>
#include <bitset>
#include <iostream>
#include <algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
int dp[1<<15][20];  // dp[S][u]：S表示已经过的节点状态，从u出发完所有剩余顶点回到起点的最短距离。
int g[15][15];  
int n, m;
void init()
{
    memset(dp, 0x3f, sizeof(dp));   // 初始化无穷大
    memset(g, 0x3f, sizeof(g)); // 邻接矩阵初始化无穷大
}
// 计算dp[S][u]
void traveling()
{
    dp[(1<<(n+1))-1][0] = 0;    // 初始边界
    for (int S = (1<<(n+1))-2; S >= 0; S--) // 枚举状态
    {
        for (int u = 0; u <= n; u++)
        {
            for (int v = 0; v <= n; v++)
            {
                if ((u != 0 && !(S>>u&1)) || g[u][v] == inf) continue;   // u!=0而且未访问或u,v不邻接
                if (!(S>>v&1) && dp[S][u] > dp[S|1<<v][v]+g[u][v]) // v未访问
                {
                    dp[S][u] = dp[S|1<<v][v] + g[u][v];
                }
            }
        }
    }
}
void floyd()
{
    for (int k = 0; k <= n; k++)
    {
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                if (g[i][j] > g[i][k] + g[k][j])
                {
                    g[i][j] = g[i][k] + g[k][j];
                }
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n && n)
    {
        init();
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                cin >> g[i][j];
            }
        }
        floyd();
        traveling();
        cout << dp[0][0] << endl;
    }
    return 0;
}