#include <cstring>
#include <bitset>
#include <iostream>
#include <algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
int dp[1<<15][20];  // dp[S][u]��S��ʾ�Ѿ����Ľڵ�״̬����u����������ʣ�ඥ��ص�������̾��롣
int g[15][15];  
int path[1<<15][15];    // ����·��
int n, m;
void init()
{
    memset(dp, 0x3f, sizeof(dp));   // ��ʼ�������
    memset(g, 0x3f, sizeof(g)); // �ڽӾ����ʼ�������
    memset(path, -1, sizeof(path)); // ��¼���·���ڵ��ǰ��
}
// ����dp[S][u]
void traveling()
{
    dp[(1<<n)-1][0] = 0;    // ��ʼ�߽�
    for (int S = (1<<n)-2; S >= 0; S--) // ö��״̬
    {
        for (int u = 0; u < n; u++)
        {
            for (int v = 0; v < n; v++)
            {
                if ((u != 0 && !(S>>u&1)) || g[u][v] == inf) continue;   // u!=0����δ���ʻ�u,v���ڽ�
                if (!(S>>v&1) && dp[S][u] > dp[S|1<<v][v]+g[u][v]) // vδ����
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
    int u, v, w;    // u,v������У�w����u��v֮��·������
    cin >> n >> m;
    init();
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        g[u][v] = w;    // ����ͼ������ͼ��˫��

    }
    traveling();
    cout << "���·����" << 0;
    print(0, 0);
    cout << endl;
    cout << "���·�����ȣ�" << dp[0][0] << endl;
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