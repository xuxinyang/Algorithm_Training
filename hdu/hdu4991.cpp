#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int mod = 123456789;
const int maxn = 1e4+5;
ll a[maxn], b[maxn];
ll dp[maxn][105];   // dp[i][j]表示前i个数上升子序列长度为j的方案数
int n, m, len;
int lowbit(int x)
{
    return x&(-x);
}
void add(int i, int j, ll val)
{
    while (i <= len) dp[i][j] += (dp[i][j] + val) % mod, i += lowbit(i);   
}
ll query(int i, int j)
{
    ll res = 0;
    while (i > 0)
    {
        res = (res + dp[i][j] % mod);
        i -= lowbit(i);
    }
    return res;
}
int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 1; i <= n; i++) 
        {
            scanf("%lld", &a[i]);
            b[i] = a[i];
        }
        memset(dp, 0, sizeof(dp));
        sort(b + 1, b + n + 1);
        len = unique(b + 1, b + n + 1) - b - 1; // 去重
        for (int i = 1; i <= n; i++)
        {
            int pos = lower_bound(b + 1, b + len + 1, a[i]) - b;
            add(pos, 1, 1);
            for (int j = 2; j <= m; j++)
            {
                int sum = query(pos - 1, j - 1);    // 求前缀和
                add(pos, j, sum);
            }
        }
        printf("%lld\n", query(len, m));
    }
    return 0;
}