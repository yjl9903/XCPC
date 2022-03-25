#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 200000 + 5;

// vector<PII> edge[maxn];
struct edge{
    int to, nxt, w;
}g[maxn * 2];
int head[maxn], cnt;
void add(int u, int v, int w){
    g[++cnt] = edge{v, head[u], w}; head[u] = cnt;
}
vector<int> v;
int n, m, q, red[maxn], last[maxn], mm[maxn] = {-1};
ll dis[maxn];

int gi(){
    int r = 0; char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') r = r * 10 + ch - '0', ch = getchar();
    return r;
}

int tot, dep[maxn], dp[maxn * 2][30], id[maxn];
void dfs(int u, int f){
    dp[++tot][0] = u; id[u] = tot;
    // for (int i = 0; i < edge[u].size(); i++){
    for (int i = head[u]; i; i = g[i].nxt){
        // int v = edge[u][i].first, w = edge[u][i].second;
        int v = g[i].to, w = g[i].w;
        if (v == f) continue;
        dep[v] = dep[u] + 1;
        if (red[v]) dis[v] = 0, last[v] = v;
        else dis[v] = dis[u] + 1ll * w, last[v] = last[u];
        dfs(v, u);
        dp[++tot][0] = u;
    }
}
void init(){
    dis[1] = tot = 0; dep[1] = last[1] = 1;
    dfs(1, 0);
    for (int j = 1; j <= mm[tot]; j++) for (int i = 1; i + (1 << j) <= tot + 1; i++)
        dp[i][j] = dep[dp[i][j - 1]] > dep[dp[i + (1 << (j - 1))][j - 1]] ? dp[i + (1 << (j - 1))][j - 1] : dp[i][j - 1];
}
int rmq(int l, int r){
    if (l > r) swap(l, r); 
    int k = mm[r - l + 1];
    // int k = 0; while ((1 << (k + 1)) <= r - l + 1) k++;
    return dep[dp[l][k]] < dep[dp[r - (1 << k) + 1][k]] ? dp[l][k] : dp[r - (1 << k) + 1][k];
}
int lca(int u, int v){
    return rmq(id[u], id[v]);
}

int check(ll m){
    int flag = 0, k = -1; ll mdis = 0;
    vector<int> tmp;
    for (int i = 0; i < v.size(); i++) {
        int x = v[i];
        if (dis[x] > m){
            if (!flag) k = x;
            else k = lca(k, x);
            flag++;
            tmp.push_back(x);
        }
        mdis = max(dis[x], mdis);
    }
    if (flag <= 1) return 1;
    for (int i = 0; i < tmp.size(); i++) if (last[k] != last[tmp[i]]) return 0;
    if (mdis - dis[k] <= m) return 1;
    else return 0;
}

int main(){
    for(int i = 1; i < maxn; i++) mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
    // int T; scanf("%d", &T);
    int T; T = gi();
    while (T--){
        // scanf("%d%d%d", &n, &m, &q);
        n = gi(); m = gi(); q = gi();
        // for (int i = 0; i <= n; i++) edge[i].clear(), red[i] = 0;
        for (int i = 0; i <= n; i++) red[i] = head[i] = 0; cnt = 0;
        // for (int i = 0, x; i < m; i++) scanf("%d", &x), red[x] = 1;
        for (int i = 0, x; i < m; i++) x = gi(), red[x] = 1;
        for (int i = 1, u, v, w; i < n; i++){
            // scanf("%d%d%d", &u, &v, &w);
            u = gi(); v = gi(); w = gi();
            // edge[u].push_back({v, w});
            // edge[v].push_back({u, w});
            add(u, v, w); add(v, u, w);
        } init();
        while (q--){
            v.clear(); ll mx = 0;
            // int nk, x; scanf("%d", &nk);
            int nk, x; nk = gi(); 
            // while (nk--) scanf("%d", &x), v.push_back(x);
            while (nk--) x = gi(), v.push_back(x), mx = max(mx, dis[x]);
            ll l = 0, r = mx, ans = 0;
            while (l <= r){
                ll m = (l + r) / 2ll;
                if (check(m)) r = m - 1, ans = m;
                else l = m + 1;
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}