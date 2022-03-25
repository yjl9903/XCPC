#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int get(){
    int x = 0; char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x;
}

int gcd(int a, int b){return b == 0 ? a : gcd(b, a % b);}

struct edge{int to, nxt;}f[2 * maxn];
int head[maxn], tot = 0;
void add(int x, int y){
    f[++tot].to = y; f[tot].nxt = head[x]; head[x] = tot;
}

int n, m, a[maxn], wt[maxn], ans[maxn];

int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn], id[maxn], vis[maxn], cnt = 0;
void dfs(int x, int d, int old){
    dep[x] = d; vis[x] = 1;
    for (int i = head[x]; i; i = f[i].nxt){
        int v = f[i].to;
        if (!vis[v]) dfs(v, d + 1, x);
    }
}
int father[maxn][30];
void init(){
    for (int j = 1; j < 30; j++) for (int i = 1; i <= n; i++) {
        if (~father[i][j - 1]){
            father[i][j] = father[father[i][j - 1]][j - 1];
        }
    }
}

int lca(int u,int v){
	if (dep[u] < dep[v]) swap(u,v);
	for (int b = 29;b >= 0;b--)
		if (dep[father[u][b]] >= dep[v])
			u = father[u][b];
	if (u == v) return u;
	for (int b = 29;b >= 0;b--)
		if (father[u][b] != father[v][b])
			u = father[u][b],v = father[v][b];
	return father[u][0];
}

int main(){
    // scanf("%d", &n); 
    n = get();
    ms(ans, -1); ms(father, -1);
    for (int i = 2, x, y; i <= n; i++){
        // scanf("%d", &x); 
        x = get();
        add(x, i); 
        father[i][0] = x;
    }
    for (int i = 1; i <= n; i++) {
        // scanf("%d", a + i); 
        a[i] = get();
    }
    dfs(1, 1, 0); init();
    for (int i = 1; i <= n; i++){
        for (int j = i + 1; j <= n; j++){
            int x = lca(i, j);
            ans[x] = max(ans[x], gcd(a[i], a[j]));
        }
    }
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}