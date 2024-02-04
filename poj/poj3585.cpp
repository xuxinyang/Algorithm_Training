#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 2e5+5;
int n, T, head[maxn], d[maxn], dp[maxn], deg[maxn], tot, ans;
struct Edge
{
    int to, next, w;
};
Edge edges[maxn<<1];
void add(int u, int v, int w)
{
    edges[++tot] = Edge{v, head[u], w};
    head[u] = tot;
}
void dfs1(int u, int fa)
{
    d[u] = 0;   // d[u]表示u向下流向的最大流量
    for (int i = head[u]; i; i = edges[i].next)
    {
        int v = edges[i].to;
        if (v == fa) continue;
        dfs1(v, u);
        if (deg[v] == 1) d[u] += edges[i].w;
        else d[u] += min(d[v], edges[i].w);
    }
}

void dfs2(int u, int fa)
{
    for (int i = head[u]; i; i = edges[i].next)
    {
        int v = edges[i].to;
        if (v == fa) continue;
        if (deg[u] == 1) dp[v] = d[v] + edges[i].w;
        else dp[v] = d[v] + min(dp[u]-min(d[v], edges[i].w), edges[i].w);
        dfs2(v, u);
    }
}

void init()
{
    memset(head, 0, sizeof(head));
    memset(d, 0, sizeof(d));
    memset(dp, 0, sizeof(dp));
    memset(deg, 0, sizeof(deg));
    tot = 0;
}
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        init();
        int u, v, w;
        for (int i = 1; i < n; i++)
        {
            scanf("%d%d%d", &u, &v, &w);
            add(u, v, w), add(v, u, w);
            deg[u]++, deg[v]++;
        }
        ans = 0;
        dfs1(1, 0);
        dp[1] = d[1];
        dfs2(1, 0);
        for (int i = 1; i <= n; i++) ans = max(ans, dp[i]);
        printf("%d\n", ans);
}
    return 0;
}