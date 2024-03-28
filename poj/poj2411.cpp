#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define ll long long
int n, m;
ll dp[2][1<<12];    // 二维滚动数组
int main()
{
    while (~scanf("%d%d", &n, &m), n+m)
    {
        memset(dp, 0, sizeof(dp));
        ll *cur, *next;
        cur = dp[0], next = dp[1];
        cur[0] = 1;
        for (int i = n-1; i >= 0; i--)
        {
            for (int j = m-1; j >= 0; j--)
            {
                for (int S = 0; S < (1<<m); S++)
                {
                    if ((S>>j)&1) // 如果不能放，直接转移
                        next[S] = cur[S&~(1<<j)];
                    else
                    {
                        ll tmp = 0; // 累计
                        if (j + 1 < m && !(S>>(j+1)&1)) // 尝试横着放
                            tmp += cur[S|1<<(j+1)];
                        if (i + 1 < n)  // 尝试竖着放
                            tmp += cur[S|1<<j];
                        next[S] = tmp;
                    }
                }
                swap(cur, next);
            }
        }
        printf("%lld\n", cur[0]);
    }
    return 0;
}