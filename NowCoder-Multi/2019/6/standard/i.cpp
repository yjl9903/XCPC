#include <map>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 200000 + 5
#define Mod 998244353
#define mp make_pair
 
int Case, n, m, tot, bcc, ord, sz, ans, Inv[N], Head[N], Dfn[N], Low[N], Sta[N], P[N];
vector<int> Bcc[N], Vec[N];
map< pair<int, int>, int > Map;
 
struct Edge
{
    int next, node, p;
}h[N << 1];
 
inline void addedge(int u, int v, int p)
{
    h[++ tot].next = Head[u], Head[u] = tot;
    h[tot].node = v, h[tot].p = p;
}
 
inline int Inc(int u, int v)
{
    return u + v - (u + v >= Mod ? Mod : 0);
}
 
void Prepare()
{
    Inv[0] = Inv[1] = 1;
    for (int i = 2; i < N; i ++)
        Inv[i] = Mod - (1LL * Inv[Mod % i] * (Mod / i) % Mod);
}
 
void dfs(int z, int fa)
{
    Dfn[z] = Low[z] = ++ ord;
    for (int i = Head[z]; i; i = h[i].next)
        if (h[i].node != fa)
        {
            int d = h[i].node, p = h[i].p;
            if (!Dfn[d])
            {
                Sta[++ sz] = d;
                dfs(d, z);
                Low[z] = min(Low[z], Low[d]);
                if (Low[d] >= Dfn[z])
                {
                    Bcc[++ bcc].push_back(z);
                    for (int j = Sta[sz]; j != z; j = Sta[-- sz])
                        Bcc[bcc].push_back(j);
                }
            }
            else Low[z] = min(Low[z], Dfn[d]);
        }
}
 
void Handle(int id)
{
    static int Dot[N], W[N], Pre[N], Suf[N];
    int cnt = Bcc[id].size();
    for (int i = 0; i < cnt; i ++)
        Dot[i] = Bcc[id][i];
    Dot[cnt] = Dot[0];
    for (int i = 0; i < cnt; i ++)
        W[i] = Map.at(minmax(Dot[i], Dot[i + 1]));
    Pre[0] = Suf[cnt] = 1;
    for (int i = 1; i <= cnt; i ++)
        Pre[i] = 1LL * Pre[i - 1] * W[i - 1] % Mod;
    for (int i = cnt - 1; i >= 0; i --)
        Suf[i] = 1LL * Suf[i + 1] * W[i] % Mod;
    if (cnt == 2)
        P[Dot[1]] = 1LL * Pre[1] * P[Dot[0]] % Mod;
    else for (int i = 1; i < cnt; i ++)
        P[Dot[i]] = 1LL * P[Dot[0]] * Inc(1, Mod - (1LL * (Mod + 1 - Pre[i]) * (Mod + 1 - Suf[i]) % Mod)) % Mod;
}
 
void DFS(int z, int fa)
{
    if (z > n)
        Handle(z - n);
    for (int d : Vec[z])
        if (d != fa)
            DFS(d, z);
}
 
int main()
{
    Prepare();
    scanf("%d", &Case);
    for (int Test = 1; Test <= Case; Test ++)
    {
        bcc = tot = ord = sz = 0;
        memset(Dfn, 0, sizeof(Dfn));
        memset(Low, 0, sizeof(Low));
        memset(Head, 0, sizeof(Head));
        for (int i = 0; i < N; i ++)
            Vec[i].clear(), Bcc[i].clear();
        Map.clear();
         
        scanf("%d%d", &n, &m);
        for (int i = 1, u, v, a, b; i <= m; i ++)
        {
            scanf("%d%d%d%d", &u, &v, &a, &b);
            int p = 1LL * a * Inv[b] % Mod;
            addedge(u, v, p);
            addedge(v, u, p);
            Map.emplace(minmax(u, v), p);
        }
        Sta[++ sz] = 1, P[1] = 1, dfs(1, 0);
        for (int i = 1; i <= bcc; i ++)
            for (int j = 0; j < Bcc[i].size(); j ++)
            {
                int u = Bcc[i][j], v = n + i;
                Vec[u].push_back(v);
                Vec[v].push_back(u);
            }
        DFS(1, 0);
        ans = 0;
        for (int i = 1; i <= n; i ++)
            ans = Inc(ans, P[i]);//, fprintf(stderr, "%d%c", P[i], i == n ? '\n' : ' ');
        printf("Case #%d: %d\n", Test, ans);
    }
    return 0;
}