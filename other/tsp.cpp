#include <cstring>
#include <bitset>
#include <iostream>
#include <algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
int dp[1<<15][20];  // dp[S][u]：S表示已经过的节点状态，从u出发完所有剩余顶点回到起点的最短距离。
int g[15][15];  
int path[1<<15][15];    // 最优路径
int n, m;
void init()
{
    memset(dp, 0x3f, sizeof(dp));   // 初始化无穷大
    memset(g, 0x3f, sizeof(g)); // 邻接矩阵初始化无穷大
    memset(path, -1, sizeof(path)); // 记录最短路径节点的前驱
}
// 计算dp[S][u]
void traveling()
{
    dp[(1<<n)-1][0] = 0;    // 初始边界
    for (int S = (1<<n)-2; S >= 0; S--) // 枚举状态
    {
        for (int u = 0; u < n; u++)
        {
            for (int v = 0; v < n; v++)
            {
                if ((u != 0 && !(S>>u&1)) || g[u][v] == inf) continue;   // u!=0而且未访问或u,v不邻接
                if (!(S>>v&1) && dp[S][u] > dp[S|1<<v][v]+g[u][v]) // v未访问
                {
                    dp[S][u] = dp[S|1<<v][v] + g[u][v];
                    path[S][u] = v;
                }
            }
        }
    }
}
void print(int S, int u)
{
    if (S == (1<<n)-1) return;
    int v = path[S][u];
    cout << "-->" << v;
    print(S|1<<v, v);
}
int main()
{
    int u, v, w;    // u,v代表城市，w代表u和v之间路径长度
    cin >> n >> m;
    init();
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        g[u][v] = w;    // 有向图，无向图存双边

    }
    traveling();
    cout << "最短路径：" << 0;
    print(0, 0);
    cout << endl;
    cout << "最短路径长度：" << dp[0][0] << endl;
    return 0;
}
/* UG
5 9
0 1 3
0 3 8
0 4 9
1 2 3
1 3 10
1 4 5
2 3 4
2 4 3
3 4 20
*/
/* DG
5 8
0 1 3
0 3 4
1 2 5
2 0 4
2 3 5
3 4 3
4 0 7
4 1 6
*/