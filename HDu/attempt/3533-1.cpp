#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int maxn = 102, maxm = 102, maxk = 102;
const int inf = 0x3fffffff;
const char badmess[20] = {"Bad luck!"};
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

struct castle
{
    int d, t, v, x, y;
    castle() { d = t = v = x = y = -1; }
    castle(int _d, int _t, int _v, int _x, int _y)
    {
        _d = d;
        _t = t;
        _v = v;
        _x = x;
        _y = y;
    }
} cas[maxk];
vector<int> row[maxn], col[maxm];

struct man
{
    int x, y, t;
    man() { x = y = t = -1; }
    man(int _x, int _y, int _t) : x(_x), y(_y), t(_t) {}
};

int charind[255];
char buff[3];
bool vis[maxn][maxm][maxk];
int m, n, k, d;

queue<man> que;

bool in(int x, int y) { return x >= 0 && x <= n && y >= 0 && y <= m; }
bool ok(int x, int y, int t, int i)
{
    castle c = cas[i];
    if (c.v == 0 && (c.x != x || c.y != y))
        return true;
    if (dx[c.d] != 0 && abs(c.x - x) % c.v == 0)
    {
        int tt = abs(c.x - x) / c.v;
        if (tt && t >= tt && (t - tt) % c.t == 0)
            return false; //存在炮弹恰巧在该时间经过该点
        if (tt == 0 && t % c.t == 0)
            return false; //如果本来就在炮台上
    }
    if (dy[c.d] != 0 && abs(c.y - y) % c.v == 0)
    {
        int tt = abs(c.y - y) / c.v;
        if (tt && t >= tt && (t - tt) % c.t == 0)
            return false;
        if (tt == 0 && t % c.t == 0)
            return false;
    }
    return true;
}
bool judge(int x, int y, int t)
{
    int sind = -1, nind = -1, wind = -1, eind = -1;
    for (int i = 0; i < (int)col[y].size(); i++)
    { //找到四个方向上最近的,这些不会遮挡其他
        int c = col[y][i];
        if (cas[c].x >= x)
        {
            if (nind == -1 || cas[nind].x > cas[c].x)
            {
                nind = c;
            }
        }
        if (cas[c].x <= x)
        {
            if (sind == -1 || cas[sind].x < cas[c].x)
            {
                sind = c;
            }
        }
    }
    for (int i = 0; i < (int)row[x].size(); i++)
    {
        int r = row[x][i];
        if (cas[r].y >= y)
        {
            if (wind == -1 || cas[wind].y > cas[r].y)
            {
                wind = r;
            }
        }
        if (cas[r].y <= y)
        {
            if (eind == -1 || cas[eind].y < cas[r].y)
            {
                eind = r;
            }
        }
    }
    if (nind != -1 && nind == sind)
        return false; //不能经过炮台
    if (wind != -1 && wind == eind)
        return false;
    if (nind != -1 && cas[nind].d == 0)
        if (!ok(x, y, t, nind))
            return false;
    if (sind != -1 && cas[sind].d == 1)
        if (!ok(x, y, t, sind))
            return false;
    if (wind != -1 && cas[wind].d == 2)
        if (!ok(x, y, t, wind))
            return false;
    if (eind != -1 && cas[eind].d == 3)
        if (!ok(x, y, t, eind))
            return false;
    return true;
}

int bfs()
{
    while (!que.empty())
        que.pop();
    vis[0][0][0] = true;
    que.push(man(0, 0, 0));
    while (!que.empty())
    {
        int nx = que.front().x, ny = que.front().y, nt = que.front().t;
        que.pop();
        //printf("(%d %d) %d\n",nx,ny,nt);
        if (nx == n && ny == m)
            return nt;
        if (nt == d)
            continue;
        if (vis[nx][ny][nt + 1] || !judge(nx, ny, nt + 1))
        {
        } //原地停留
        else
        {
            vis[nx][ny][nt + 1] = true;
            que.push(man(nx, ny, nt + 1));
        }
        for (int i = 0; i < 4; i++)
        {
            int tx = nx + dx[i], ty = ny + dy[i];
            if (!in(tx, ty) || vis[tx][ty][nt + 1])
                continue;
            if (judge(tx, ty, nt + 1))
            { //移动
                vis[tx][ty][nt + 1] = true;
                que.push(man(tx, ty, nt + 1));
            }
        }
    }
    return -1;
}
int main()
{
    charind['N'] = 0;
    charind['S'] = 1;
    charind['W'] = 2;
    charind['E'] = 3;

    while (scanf("%d%d%d%d", &n, &m, &k, &d) == 4)
    {
        memset(vis, false, sizeof(vis));
        for (int i = 0; i < maxn; i++)
        {
            row[i].clear();
        }
        for (int i = 0; i < maxm; i++)
        {
            col[i].clear();
        }

        for (int i = 0; i < k; i++)
        {
            scanf("%s", buff);
            cas[i].d = charind[(int)buff[0]];
            scanf("%d%d%d%d", &cas[i].t, &cas[i].v, &cas[i].x, &cas[i].y);
            col[cas[i].y].push_back(i);
            row[cas[i].x].push_back(i);
        }
        int ans = bfs();
        if (ans == -1)
            puts(badmess);
        else
            printf("%d\n", ans);
    }

    return 0;
}