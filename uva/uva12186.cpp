#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 1e6+5;
int n, t, a[maxn];
vector<int> ve[maxn];
int dfs(int u)
{
    if (ve[u].size() == 0) return 1;
    int k = ve[u].size();
    vector<int> tmp;
    for (int i = 0; i < k; i++)
    {
        int v = ve[u][i];
        tmp.push_back(dfs(v));
    }
    sort(tmp.begin(), tmp.end());
    int m = (k * t - 1) / 100 + 1, ans = 0;
    for (int i = 0; i < m; i++)
        ans += tmp[i];
    return ans; 
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n >> t)
    {
        if (n == 0 && t == 0) break;
        for (int i = 0; i <= n; i++) ve[i].clear(); 
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            ve[a[i]].push_back(i);
        }
        cout << dfs(0) << "\n";
    }
    return 0;
}