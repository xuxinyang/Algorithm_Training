#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 30;
int dig[30], T;
ll dp[maxn][2], z[maxn], n;
// dp[pos][sta]表示当前第pos位，sta状态下满足条件的个数，sta表示前一位是否是4，只有0和1两种状态
ll dfs(int pos, bool sta, bool limit)
{
    if (pos == 0) return 0;
    if (!limit && dp[pos][sta] != -1) return dp[pos][sta];
    int len = limit ? dig[pos]:9;
    ll ans = 0;
    for (int i = 0; i <= len; i++)
    {
        if (sta && i == 9)
            ans += limit?n%z[pos-1]+1:z[pos-1];
        else
            ans += dfs(pos-1, i==4, limit&&i==len);
    }
    if (!limit) dp[pos][sta] = ans;
    return ans;
}
ll solve(ll x)
{
    int pos = 0;
    while (x)
    {
        dig[++pos] = x % 10;
        x /= 10;
    }
    return dfs(pos, 0, 1);
}
int main()
{
    memset(dp, -1, sizeof(dp));
    z[0] = 1;
    for (int i = 1; i < maxn; i++) z[i] = z[i-1]*10;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld", &n);
        printf("%lld\n", solve(n));
    }
    return 0;
}