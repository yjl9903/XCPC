#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

struct edge{int to, nxt;}f[maxn * 4];
int head[maxn], tot;
void add(int x, int y){f[++tot] = {y, head[x]}; head[x] = tot;}

int n, m, q;

int dfn[maxn], low[maxn], fa[maxn], dep[maxn], cnt, bridge, cut[maxn];
void dfs(int p, int old){
    dfn[p] = low[p] = ++cnt;
    dep[p] = dep[old] + 1;
    for (int i = head[p]; i; i = f[i].nxt){
        int v = f[i].to;
        if (v == old) continue;
        if (!dfn[v]){
            fa[v] = p; dfs(v, p);
            low[p] = min(low[p], low[v]);
            if (low[v] > dfn[p]){
                bridge++;
                cut[v] = 1;
            }
        }
        else low[p] = min(low[p], dfn[v]);
    }
}

void lca(int x, int y){
    if (dfn[x] < dfn[y]) swap(x, y);
    while (dfn[x] > dfn[y]){
        if (cut[x]) bridge--, cut[x] = 0;
        x = fa[x];
    }
    while (x != y){
        if (cut[x]) bridge--, cut[x] = 0;
        if (cut[y]) bridge--, cut[y] = 0;
        x = fa[x], y = fa[y];
    }
}

int main(){
    int kase = 0;
    while (~scanf("%d%d", &n, &m)){
        if (!n && !m) break;
        ms(head, 0); tot = 0; 
        while (m--){
            int x, y; scanf("%d%d", &x, &y);
            add(x, y); add(y, x);
        }
        cnt = bridge = 0; ms(dfn, 0); ms(cut, 0); dep[0] = fa[1] = 0; dfs(1, 0);
        scanf("%d", &q); int x, y;
        printf("Case %d:\n", ++kase);
        while (q--){
            scanf("%d%d", &x, &y);
            lca(x, y); printf("%d\n", bridge);
        }
        puts("");
    }
    return 0;
}