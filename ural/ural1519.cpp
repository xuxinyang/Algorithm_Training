#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define ll long long
const int HASH = 40013; // 哈希值设置合适些，太大太小都可能会超时
ll dp[2][1<<24];    // 记录方案数
int state[2][1<<24];    // 记录状态，S = state[pre][s], pre为前一个格子标记，s为状态编号，S为状态
int total[2];   // 记录状态总数
int pre, now;
int endx, endy; // 记录最后一个非障碍格子
bool map[15][15]; 
int n, m;
int Hash[HASH];   // 记录S对应的哈希值x的状态编号
ll ans;
void HashIn(int S, ll num)
{
    int x = S % HASH;
    while (~Hash[x] && state[now][Hash[x]] != S) // 线性探测
    {
        x++;
        x %= HASH;
    }
    if (Hash[x] == -1) // 未找到，加入hash中
    {
        dp[now][total[now]] = num;
        state[now][total[now]] = S;
        Hash[x] = total[now];   // 记录状态编号
        total[now]++;
    }
    else dp[now][Hash[x]] += num;
}
void init()
{
    memset(map, 0, sizeof(map));
    endx = -1;  // 最后一个非障碍格子
    for (int i = 0; i < n; i++)
    {
        char str[200];
        scanf("%s", str);
        for (int j = 0; j < m; j++)
        {
            if (str[j] == '*') map[i][j] = 0;
            else if (str[j] == '.') map[i][j] = 1, endx = i, endy = j;
        }
    }
}
// 位运算，取S按长度l的第p位
int getV(int S, int p, int l = 2)   // 4进制，l=2
{
    return (S>>(p*l)) & ((1<<l)-1);
}
// 位运算，设置S按长度l的第p位值为v
void setV(int &S, int p, int v, int l = 2)
{
    S ^= getV(S, p) << (p*l);   // 第p位为0
    S |= v << (p * l);  // 第p位置v
}
// 清空哈希表
void memsetnow()
{
    memset(Hash, -1, sizeof(Hash));
    total[now] = 0;
}
void solve()
{
    if (endx == -1) // 没有非障碍格子
    {
        puts("0");
        return;
    }
    pre = 0, now = 1;
    ans = 0;
    dp[pre][0] = 1;
    state[pre][0] = 0;  // 记录前一个已经确定格子的状态
    total[pre] = 1; // 记录前一个已确定格子的状态编号
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            memsetnow();
            for (int s = 0; s < total[pre]; s++)    // 枚举前一个已确定格子的所有状态编号
            {
                ll num = dp[pre][s];    // 读取前一个方案数
                int S = state[pre][s];  // 读取前一个状态
                int p = getV(S, j); // 得到第j位
                int q = getV(S, j+1);   // 得到第j+1位置
                if (map[i][j] == 0) // 有障碍，case1
                {
                    if (p == 0 && q == 0) HashIn(S, num);   // 插入哈希表
                    continue;
                }
                if (p == 0 && q == 0)   // p，q均为0，case2
                {
                    if (map[i+1][j] && map[i][j+1])
                    {
                        int nS = S;
                        setV(nS, j, 1); // 第j位置改为1
                        setV(nS, j+1, 2);   // 第j+1位改为2
                        HashIn(nS, num);
                    }
                    continue;
                }
                if ((p > 0) ^ (q > 0))  // p,q有一个为0， case3
                {
                    if (map[i+(p>0)][j+(q>0)]) HashIn(S, num);  // 状态不变
                    if (map[i+(q>0)][j+(p>0)])
                    {
                        int nS = S;
                        setV(nS, j, q); // 交换p，q
                        setV(nS, j+1, p);
                        HashIn(nS, num);
                    }
                    continue;
                }
                if (p == 1 && q == 1)   // case 4.1
                {
                    int find = 1;
                    for (int v = j + 2; v <= m; v++)    // 向后搜q匹配的右边括号，改为左括号
                    {
                        int k = getV(S, v); // 得到第v位
                        if (k == 1) find++;
                        else if (k == 2) find--;
                        if (find == 0)
                        {
                            int nS = S;
                            setV(nS, j, 0); // p,q置为0
                            setV(nS, j+1, 0);
                            setV(nS, v, 1); // 改为左括号
                            HashIn(nS, num);
                            break;
                        } 
                    }
                    continue;
                }
                if (p == 2 && q == 2)   // case 4.2
                {
                    int find = 1;
                    for (int v = j-1; v >= 0; v--)  // 向前搜p匹配的左括号，改为右括号
                    {
                        int k = getV(S, v); // 得到第v位
                        if (k == 2) find++;
                        else if (k == 1) find--;
                        if (find == 0)
                        {
                            int nS = S;
                            setV(nS, j, 0); // p,q置为0
                            setV(nS, j+1, 0);
                            setV(nS, v, 2); // 改为右边括号
                            HashIn(nS, num);
                            break;
                        }
                    }
                    continue;
                }
                if (p == 2 && q == 1)   // case 4.3
                {
                    int nS = S;
                    setV(nS, j, 0); // p,q置为0
                    setV(nS, j+1, 0);
                    HashIn(nS, num);
                    continue;
                }
                if (p == 1 && q == 2)   // case 4.4
                    if (i == endx && j == endy) // 最后一个非障碍格子
                        ans += num;
            }
            swap(now, pre);
        }
        memsetnow();
        for (int s = 0; s < total[pre]; s++)    // 换行
        {
            ll num = dp[pre][s];
            int S = state[pre][s] << 2; // 左移一格，四进制，一格用两位表示
            HashIn(S, num);
        }
        swap(now, pre);
    }
    printf("%lld\n", ans);
}
int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        init();
        solve();
    }
    return 0;   
}