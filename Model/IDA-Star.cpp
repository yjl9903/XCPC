// UVa11212 Editing a book

#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, a[10], maxd;

int getH()
{
    int s = 0;
    for (int i = 1; i < n; i++)
        if (a[i] - a[i - 1] != 1)
            s++;
    return s;
}

bool dfs(int p)
{
    if (p == maxd)
    {
        if (!getH())
            return true;
        return false;
    }
    if (3 * p + getH() > 3 * maxd)
        return false;

    int src[9];
    memcpy(src, a, sizeof a);
    for (int l = 0; l < n; l++)
    {
        for (int r = l; r < n; r++)
        {
            for (int i = 0; i < l; i++)
            {
                int c = 0;
                for (; c < i; c++)
                    a[c] = src[c];
                for (int j = l; j <= r; j++, c++)
                    a[c] = src[j];
                for (int j = i; j < n; j++)
                {
                    if (j >= l && j <= r)
                        continue;
                    a[c++] = src[j];
                }
                if (dfs(p + 1))
                    return true;
            }
            for (int i = r + 1; i < n; i++)
            {
                int c = 0;
                for (int j = 0; j <= i; j++)
                {
                    if (j >= l && j <= r)
                        continue;
                    a[c++] = src[j];
                }
                for (int j = l; j <= r; j++, c++)
                    a[c] = src[j];
                for (int j = i + 1; j < n; j++, c++)
                    a[c] = src[c];
                if (dfs(p + 1))
                    return true;
            }
        }
    }
    return false;
}

int main()
{
    int kase = 0;
    while (cin >> n && n)
    {
        for (int i = 0; i<n; cin>> a[i++])
            ;
        int flag = 0;
        int src[9];
        memcpy(src, a, sizeof a);
        for (maxd = 0; maxd < 9 && !flag; maxd++)
        {
            memcpy(a, src, sizeof a);
            flag = dfs(0);
        }
        cout << "Case " << ++kase << ": ";
        cout << maxd - 1 << endl;
    }
    return 0;
}