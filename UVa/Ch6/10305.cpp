#include <iostream>
#include <cstring>
#define maxn 105
using namespace std;

bool map[maxn][maxn];
int res[maxn], check[maxn], n, m, tot;

bool dfs(int x)
{
    check[x] = -1;
    //cout << x << endl;
    for (int v = 1; v <= n; v++)
        if (map[x][v])
        {
            if (check[v] < 0)
                return false;
            else if (!check[v])
                if (!dfs(v))
                    return false;
        }
    check[x] = 1;
    res[tot--] = x;
    //cout << x << endl;
    return true;
}

bool toposort()
{
    tot = n;
    memset(check, 0, sizeof check);
    for (int i = 1; i <= n; i++)
    {
        if (!check[i])
            if (!dfs(i))
                return false;
    }
    return true;
}

int main()
{   
    while (cin >> n >> m)
    {
        if (!n && !m)   break;
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                map[i][j] = 0;
        for (int i = 0; i < m; i++)
        {
            int x, y;
            cin >> x >> y;
            map[x][y] = 1;
        }
        toposort();
        cout << res[1];
        for (int i = 2; i <= n; i++)
            cout << ' ' << res[i];
        cout << endl;
    }
    return 0;
}