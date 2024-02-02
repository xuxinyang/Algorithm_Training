#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 6005;
int n, fa[maxn], dp[maxn][2], a[maxn];
vector<int> ve[maxn];
void init()
{
    int u, v;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i]; fa[i] = -1;
        ve[i].clear();
    }
    while (cin >> u >> v)
    {
        if (!u && !v) break;
        ve[v].push_back(u);
        fa[u] = v;
    
    }
}
void dfs(int u)
{
    dp[u][0] = 0, dp[u][1] = a[u];
    for (int i = 0; i < ve[u].size(); i++)
    {
        int v = ve[u][i];
        dfs(v);
        dp[u][0] += max(dp[v][0], dp[v][1]);
        dp[u][1] += dp[v][0];
    }

}
void solve()
{
    int root = 1;
    while (fa[root] != -1) root = fa[root];
    dfs(root);
    cout << max(dp[root][0], dp[root][1]) << "\n";
}
int main()
{
    while (cin >> n)
    {
        init();
        solve();
    }
    return 0;
}