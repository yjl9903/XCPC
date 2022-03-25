#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 200000 + 5;

// vector<int> edge[maxn];
struct edge { int to, nxt; } g[maxn * 2];
int tot, head[maxn];
void add(int u, int v) {
    g[++tot] = { v, head[u] }; head[u] = tot;
}

int n, m, tag[maxn];

namespace hld {
    int dp[maxn][20], dep[maxn], dis[maxn];
    void dfs(int u, int fa){
        dp[u][0] = fa; dep[u] = dep[fa] + 1;
        for (int i = head[u]; i; i = g[i].nxt){
            int v = g[i].to;
            if (v == fa) continue;
            dfs(v, u);
        }
    }
    void init(){
        ms(dp, 0); dep[0] = dis[0] = 0;
        dfs(1, 0); 
        for (int j = 1; j < 20; j++) 
            for (int i = 1; i <= n; i++) 
                dp[i][j] = dp[dp[i][j - 1]][j - 1];
    }
    int qlca(int x, int y){
        if (dep[x] < dep[y]) swap(x, y);
        int tmp = dep[x] - dep[y];
        for (int i = 0; tmp; i++, tmp >>= 1)
            if (tmp & 1) x = dp[x][i];
        if (x == y) return x;
        for (int i = 19; i >= 0; i--){
            if (dp[x][i] != dp[y][i]){
                x = dp[x][i]; y = dp[y][i];
            }
        }
        return dp[x][0];
    }
}

int ans;
void dfs(int u, int f) {
    // for (int& v: edge[u]) {
    for (int i = head[u]; i; i = g[i].nxt) {
        int v = g[i].to;
        if (v == f) continue;
        dfs(v, u);
        tag[u] += tag[v];
        if (tag[v] == 1) ans++;
        if (tag[v] == 0) ans += m;
    }
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        add(u, v); add(v, u);
        // edge[u].push_back(v);
        // edge[v].push_back(u);
    } hld::init();
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v);
        tag[u]++; tag[v]++; tag[hld::qlca(u, v)] -= 2;
    }
    dfs(1, 0);
    cout << ans << endl;
    return 0;
}