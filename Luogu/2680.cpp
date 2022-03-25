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
const int maxn = 300000 + 5;

int gi(){
    char ch=getchar();int x=0;
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x;
}

// vector<PII> edge[maxn];
struct node{
    int to, nxt, d;
}edge[maxn * 2];
int tot, head[maxn];
void add(int x, int y, int d){
    edge[++tot] = {y, head[x], d}; head[x] = tot;
}

int n, m;
PII que[maxn]; int qlca[maxn], qdis[maxn];

int fa[maxn][30], dep[maxn], dis[maxn];
void dfs1(int u, int f){
    fa[u][0] = f; dep[u] = dep[f] + 1;
    // for (auto& x : edge[u]){
    for (int i = head[u]; i; i = edge[i].nxt){
        int v = edge[i].to;
        if (v == f) continue;
        // dis[x.first] = dis[u] + x.second;
        dis[v] = dis[u] + edge[i].d;
        dfs1(v, u);
    }
}
void init(){
    dfs1(1, 0);
    for (int j = 1; j <= 20; j++)
        for (int i = 1; i <= n; i++)
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
}
int lca(int x, int y){
    if (dep[x] < dep[y]) swap(x, y);
    int tmp = dep[x] - dep[y];
    for (int i = 0; tmp; i++, tmp >>= 1)
        if (tmp & 1) x = fa[x][i];
    if (x == y) return x;
    for (int i = 20; i >= 0; i--)
        if (fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}

int cnt, mn, tag[maxn];
int dfs(int u, int f){
    // for (auto& x : edge[u]){
    for (int i = head[u]; i; i = edge[i].nxt){
        // int v = x.first;
        int v = edge[i].to;
        if (v == f) continue;
        if (dfs(v, u)) return 1;
        tag[u] += tag[v];
        // if (tag[v] == cnt && x.second >= mn) return 1; 
        if (tag[v] == cnt && edge[i].d >= mn) return 1; 
    }
    return 0;
}
int check(int x){
    mn = 0; cnt = 0; ms(tag, 0);
    for (int i = 0; i < m; i++){
        if (qdis[i] <= x) continue;
        cnt++; mn = max(mn, qdis[i] - x);
        tag[que[i].first]++; tag[que[i].second]++; tag[qlca[i]] -= 2;
    }
    return !cnt || dfs(1, 0);
}

int main(){
    // scanf("%d%d", &n, &m);
    n = gi(); m = gi();
    for (int i = 1, a, b, t; i < n; i++){
        // scanf("%d%d%d", &a, &b, &t);
        a = gi(); b = gi(); t = gi();
        // edge[a].push_back({b, t});
        // edge[b].push_back({a, t});
        add(a, b, t); add(b, a, t);
    } init();
    
    for (int i = 0, a, b; i < m; i++){
        // scanf("%d%d", &a, &b); 
        a = gi(); b = gi();
        que[i] = make_pair(a, b);
        int x = lca(a, b); qlca[i] = x; 
        qdis[i] = dis[a] + dis[b] - 2 * dis[x];
    }
    int l = 0, r = 1e9, ans = 0;
    while (l <= r){
        int m = (l + r) / 2;
        if (check(m)) r = m - 1, ans = m;
        else l = m + 1;
    }
    printf("%d\n", ans);
    return 0;
}