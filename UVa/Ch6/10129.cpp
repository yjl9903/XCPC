#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int G[30][30], vis[30], have[30];
char x[1010];

void dfs(int p)
{
    vis[p] = 1;
    for (int i = 0; i < 26; i++)
    {
        if (p != i && G[p][i] && !vis[i])
        {
            dfs(i);
        }
    }
}

bool judge()
{
    for (int i = 0; i < 26; i++)
    {
        if (have[i] && !vis[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int T, n;
    cin >> T;
    while (T--)
    {
        memset(G, 0, sizeof G);
        memset(vis, 0, sizeof vis);
        memset(have, 0, sizeof have);
        cin >> n;
        while (n--)
        {
            cin >> x;
            G[x[0] - 'a'][x[strlen(x) - 1] - 'a']++;
            have[x[0] - 'a']++;
            have[x[strlen(x) - 1] - 'a']++;
        }

        int in[30], out[30], flag = 0;
        memset(in, 0, sizeof in);   memset(out, 0, sizeof out);
        for (int i = 0; i < 26; i++)
        {
            for (int j = 0; j < 26; j++)
            {
                in[i] += G[j][i];
                out[i] += G[i][j];
            }
        }
        for (int i = 0; i < 26; i++)
        {
            if (have[i])
                if (in[i] - out[i] == 1 || out[i] - in[i] == 1)
                    flag++;
                else if (in[i] != out[i])
                {
                    flag = -1;
                    break;
                }
        }

        for (int i = 0; i < 26; i++)
            for (int j = 0; j < 26; j++)
                if (G[i][j])
                    G[j][i] = G[i][j];

        if (flag == 0 || flag == 2)
        {
            for (int i = 0; i < 26; i++)
                if (have[i])
                {
                    dfs(i);
                    break;
                }
            if (judge())
                cout << "Ordering is possible.\n";
            else
                cout << "The door cannot be opened.\n";
        }
        else
            cout << "The door cannot be opened.\n"; 
    }
    return 0;
}