#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

struct edge{int to, nxt;}f[4 * maxn];
int head[maxn], cnt;
void add(int x, int y){
    f[++cnt].to = y; f[cnt].nxt = head[x]; head[x] = cnt;
}

int n, m, q;
int tot = 0, dfn[maxn], low[maxn], dep[maxn], fa[maxn];
int cut[maxn], br;

void dfs(int p, int old){
    dfn[p] = low[p] = ++tot;
    dep[p] = dep[old] + 1;
    for (int i = head[p]; i; i = f[i].nxt){
        int v = f[i].to;
        if (v == old) continue;
        if (!dfn[v]){
            fa[v] = p; dfs(v, p);
            low[p] = min(low[p], low[v]);
            if (low[v] > dfn[p]){
                cut[v] = 1;
                br++;
            }
        }
        else low[p] = min(low[p], dfn[v]);
    }
}

void lca(int x, int y){
    if (dfn[x] < dfn[y]) swap(x, y);
    while (dfn[x] > dfn[y]){
        if (cut[x]) {
            br--; cut[x] = 0;
        }
        x = fa[x];
    }
    while (x != y){
        if (cut[x]){
            br--; cut[x] = 0;
        }
        if (cut[y]){
            br--; cut[y] = 0;
        }
        x = fa[x]; y = fa[y];
    }
}

void init(){
    ms(head, 0); cnt = 0;
    ms(dfn, 0); tot = 0; 
    ms(cut, 0); br = 0;
    dep[0] = fa[1] = 0;
}

int main(){
    int kase = 0;
    while (~scanf("%d%d", &n, &m)){
        if (!n && !m) break;
        init();
        while (m--){
            int x, y; scanf("%d%d", &x, &y);
            add(x, y); add(y, x);
        }
        dfs(1, 0);
        scanf("%d", &q);
        printf("Case %d:\n", ++kase);
        int kas = 0;
        while (q--){
            int x, y; scanf("%d%d", &x, &y);
            lca(x, y); printf("%d\n", br);
        }
        puts("");
    }
    return 0;
}