#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define ll long long
int dig[15], pos;
ll dp[15][10][15], ans[2][10];
/** 
 * @brief 统计每个数字出现多少次
 * 
 * @param pos  第几位
 * @param val 0-9哪个数字
 * @param cnt 出现次数
 * @param lead 前导0
 * @param limit 到了限制位？
 * @return ll 
 */
ll dfs(int pos, int val, int cnt, bool lead, bool limit)
{
    if (pos == 0) return cnt;
    // 没有限制，无前导0，而且已经赋值
    if (!limit && !lead && dp[pos][val][cnt] != -1) return dp[pos][val][cnt];
    int len = limit?dig[pos]:9, t = 0;
    ll ans = 0;
    for (int i = 0; i <= len; i++)
    {
        if (val != i) t = cnt;
        else 
        {
            // 有前导0，而且统计0的出现次数，不计算
            if (lead && val == 0) t = 0;
            else t = cnt + 1;
        }
        ans += dfs(pos-1, val, t, lead&&i==0, limit&&i==len);
    }
    if (!limit && !lead) dp[pos][val][cnt] = ans;
    return ans;
}
/**
 * @brief 数位拆分
 * 
 * @param x 
 * @param idx 
 * idx = 0，记录[1,a]区间0-9数字出现次数，idx=1，记录[1,b]区间0-9出现次数
 */
void solve(ll x, int idx)
{
    if (x == 0) return;
    int pos = 0;
    while (x)
    {
        dig[++pos] = x % 10;
        x /= 10;
    }
    for (int i = 0; i < 10; i++)
        ans[idx][i] = dfs(pos, i, 0, 1, 1);
}
int main()
{
    ios::sync_with_stdio(false);
    memset(dp, -1, sizeof(dp));
    ll a, b;
    while (~scanf("%lld%lld", &a, &b), a+b)
    {
        if (a > b) swap(a, b);
        memset(ans, 0, sizeof(ans));
        solve(a-1, 0), solve(b, 1);
        for (int i = 0; i < 10; i++)
        {
            printf("%lld ", ans[1][i]-ans[0][i]);
        }
        printf("\n");
    }
    return 0;
}