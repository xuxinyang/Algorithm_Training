#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, m;
char map[110][20], num[100], top;
int stk[100], cur[100];
int dp[110][100][100];
bool check(int x)   // 判断该状态是否合法，横向检测相邻1之间的距离不能小于3
{
    if (x & (x << 1)) return 0;
    if (x & (x << 2)) return 0;
    return 1;
}
void init() // 记录所有可能的合法状态，最多60种
{
    top = 0;
    for (int i = 0; i < (1 << m); i++)
        if (check(i)) stk[top++] = i;
}
bool fit(int x, int k)  // 判断状态x是否与地图第k行匹配，确保炮兵部队部署在平原上
{
    if (cur[k] & x) return 0;
    return 1;
}
int count(int x)    // 统计状态x的二进制中有多少个1，即炮兵个数
{
    int cnt = 0;
    while (x)
    {
        cnt++;
        x &= (x-1);
    }
    return cnt;
}
int solve()
{
    int ans = 0;
    memset(dp, -1, sizeof(dp));
    for (int j = 0; j < top; j++)   // 初始化第一行
    {
        num[j] = count(stk[j]);
        if (fit(stk[j], 1))
        {
            dp[1][j][0] = num[j];   // 第一行状态为j，上一行状态为第0个状态，即000000
            ans = max(ans, dp[1][j][0]);
        }
    }
    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j < top; j++)
        {
            if (!fit(stk[j], i)) continue;  // 匹配检测
            for (int k = 0; k < top; k++)   
            {
                if (stk[j] & stk[k]) continue;    // 竖向检测，与上一行不能有相邻1
                for (int t = 0; t < top; t++)
                {
                    if (stk[j] & stk[t]) continue;  // 竖向检测，与上上行不能有相邻1
                    if (dp[i-1][k][t] == -1) continue;  // 无效
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][k][t] + num[j]); 
                }
                if (i == n) ans = max(ans, dp[i][j][k]);
            }
        }
    }
    return ans;
}
int main()
{
    scanf("%d%d", &n, &m);
    init();
    for (int i = 1; i <= n; i++) scanf("%s", map[i]+1);
    for (int i = 1; i <= n; i++)
    {
        cur[i] = 0;
        for (int j = 1; j <= m; j++)
            if (map[i][j] == 'H') cur[i] += (1<<(j-1));
    }
    printf("%d\n", solve());
    return 0;
}