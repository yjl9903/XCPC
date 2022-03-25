#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
const int md = 370000 + 7;
char cmd[7];
queue<int> q;
char tab[5][5];
string state[md];
const int dx[] = {0, 0, -1, 1}; /// 0 - l, 1 - r, 2 - u, 3 - d;
const int dy[] = {-1, 1, 0, 0};
const char *flag = "rldu";
int jie[10];
void init()
{
    jie[0] = jie[1] = 1;
    for (int i = 2; i < 9; ++i)
    {
        jie[i] = jie[i - 1] * i;
    }
}
char hashs[10];
int Hash(int v)
{
    for (int i = 0; i < 9; ++i)
    {
        hashs[9 - i - 1] = v % 10 + 48;
        v /= 10;
    }
    int ans = 0;
    for (int i = 0; i < 9; ++i)
    {
        int sum = 0;
        for (int j = i + 1; j < 9; ++j)
        {
            if (hashs[j] < hashs[i])
                ++sum;
        }
        ans += sum * jie[9 - i - 1];
    }
    return ans;
}
bool vis[md];
void bfs(int vvvv)
{
    while (!q.empty())
        q.pop();
    q.push(vvvv);
    int v = 0;
    string tu = "";
    vis[Hash(vvvv)] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        int idu = Hash(u);
        tu = "";
        for (int i = 0; i < 9; ++i)
        {
            tu += u % 10 + 48;
            u /= 10;
        }
        reverse(tu.begin(), tu.end());
        int pos;
        for (pos = 0; pos < 9; ++pos)
            if (tu[pos] == '0')
                break;

        for (int i = 0; i < 9; ++i)
        {
            tab[i / 3][i % 3] = tu[i];
        }
        int x = pos / 3;
        int y = pos % 3;
        for (int i = 0; i < 4; ++i)
        {
            int xx = dx[i] + x;
            int yy = dy[i] + y;
            if (xx >= 0 && xx <= 2 && yy >= 0 && yy <= 2)
            {
                swap(tab[x][y], tab[xx][yy]);
                v = 0;
                for (int j = 0; j < 3; ++j)
                {
                    for (int k = 0; k < 3; ++k)
                    {
                        v = v * 10 + tab[j][k] - 48;
                    }
                }
                int idv = Hash(v);
                if (!vis[idv])
                {
                    vis[idv] = 1;
                    state[idv] = state[idu] + flag[i];
                    q.push(v);
                }
                swap(tab[x][y], tab[xx][yy]);
            }
        }
    }
}

int main()
{
    init();
    //    printf("%d\n",Hash(876543210));
    memset(vis, 0, sizeof vis);
    for (int i = 0; i < md; ++i)
    {
        state[i] = "";
    }
    bfs(123456780);
    for (int i = 0; i < md; ++i)
    {
        reverse(state[i].begin(), state[i].end());
    }
    while (~scanf("%s", cmd))
    {
        if (cmd[0] == 'x')
            cmd[0] = 48;
        int v = cmd[0] - 48;
        for (int i = 1; i < 9; ++i)
        {
            scanf("%s", cmd);
            if (cmd[0] == 'x')
                cmd[0] = '0';
            v = v * 10 + cmd[0] - 48;
        }
        if (!vis[Hash(v)])
            puts("unsolvable");
        else
            printf("%s\n", state[Hash(v)].c_str());
    }
    return 0;
}