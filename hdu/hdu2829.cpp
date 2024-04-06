#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1e3+5;
int n, m, idx, head, tail;
int s[maxn], q[maxn];
int dp[maxn][2], cost[maxn], sum[maxn]; // dp为滚动数组
int getY(int k1, int k2)
{
    return dp[k2][idx^1]-cost[k2]+sum[k2]*sum[k2]-(dp[k1][idx^1]-cost[k1]+sum[k1]*sum[k1]);
}
int getX(int k1, int k2)
{
    return sum[k2] - sum[k1];
}
int getVal(int i, int k)
{
    return dp[k][idx^1] + cost[i]-cost[k]-sum[i]*sum[k] + sum[k]*sum[k];
}
void solve()
{
    idx = 0;
    for (int i = 1; i <= n; i++) dp[i][idx] = cost[i];
    for (int j = 1; j <= m; j++)    // 分成j段
    {
        idx ^= 1;
        head = tail = 0;
        q[tail++] = 0;
        for (int i = 1; i <= n; i++)
        {
            while (head+1<tail && getY(q[head], q[head+1])<=getX(q[head], q[head+1])*sum[i]) head++;
            dp[i][idx] = getVal(i, q[head]);
            dp[i][idx] = getVal(i, q[head]);
            while (head+1<tail && getY(q[tail-1], i)*getX(q[tail-2], q[tail-1])<=getY(q[tail-2],q[tail-1])*getX(q[tail-1], i))
                tail--;
            q[tail++] = i;
        }
    }
}
int main()
{
    while (~scanf("%d%d", &n, &m), n+m)
    {
        for (int i = 1; i <= n; i++) scanf("%d", &s[i]);
        for (int i = 1; i <= n; i++) sum[i] = sum[i-1] + s[i];
        memset(cost, 0, sizeof(cost));
        for (int i = 1; i <= n; i++)
            for (int j = i+1; j <= n; j++)
                cost[j] += s[i]*s[j];
        for (int i = 1; i <= n; i++) cost[i] += cost[i-1];
        solve();
        printf("%d\n", dp[n][idx]);
    }
    return 0;
}