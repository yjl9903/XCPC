#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 362880 + 5;

int n, a[9], st[maxn][9], f[10], vis[maxn];

int cantor(int x[])
{
    int s = 0;
    for (int i = 0; i < n; i++)
    {
        int t = 0;
        for (int j = i + 1; j < n; j++)
        {
            if (x[i] > x[j])
                t++;
        }
        s += t * f[n - 1 - i];
    }
    return s;
}

void show(int x[])
{
    for (int i = 0; i < n; cout << x[i++] << ' ')
        cout << endl;
}

int bfs()
{
    ms(vis, 0);
    int cnt = 1;
    queue<PII> q;
    vis[cantor(st[1])] = 1;
    q.emplace(cnt, 0);
    while (!q.empty())
    {
        PII t = q.front();
        q.pop();
        if (t.second > 8)
            continue;
        if (cantor(st[t.first]) == 0)
            return t.second;
        int l = 0, r = 0, x[9];
        memcpy(a, st[t.first], sizeof st[t.first]);

        for (l = 0; l < n; l++)
        {
            for (r = l; r < n; r++){
                for (int i = 0; i < l; i++)
                {
                    int c = 0;
                    for (; c < i; c++)
                        x[c] = a[c];
                    for (int j = l; j <= r; j++, c++)
                        x[c] = a[j];
                    for (int j = i; j < n; j++)
                    {
                        if (j >= l && j <= r)
                            continue;
                        x[c++] = a[j];
                    }
                    // show(x);
                    int h = cantor(x);
                    if (!vis[h])
                    {
                        memcpy(st[++cnt], x, sizeof x);
                        vis[h] = 1;
                        q.emplace(cnt, t.second + 1);
                    }
                }
                for (int i = r + 1; i < n; i++)
                {
                    int c = 0;
                    for (int j = 0; j <= i; j++)
                    {
                        if (j >= l && j <= r)
                            continue;
                        x[c++] = a[j];
                    }
                    for (int j = l; j <= r; j++, c++)
                        x[c] = a[j];
                    for (int j = i + 1; j < n; j++, c++)
                        x[c] = a[c];
                    // show(x);
                    int h = cantor(x);
                    if (!vis[h])
                    {
                        memcpy(st[++cnt], x, sizeof x);
                        vis[h] = 1;
                        q.emplace(cnt, t.second + 1);
                    }
                }
            }
        }
    }
    return 0;
}

int main()
{
    f[0] = 1;
    int kase = 0;
    for (int i = 1; i < 11; i++)
    {
        f[i] = f[i - 1] * i;
    }
    while (cin >> n && n)
    {
        for (int i = 0; i<n; cin>> st[1][i++])
            ;
        int res = bfs();
        cout << "Case " << ++kase << ": ";
        cout << res << endl;
    }
    return 0;
}