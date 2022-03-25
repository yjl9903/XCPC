#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

vector<PII> edge[maxn];
int n, q, que[200], ans[200];

int siz[maxn], vis[maxn], rt, mn, sum;
void getrt(int u, int f) {
    siz[u] = 1;
    int t = 0;
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == f || vis[v]) continue;
        getrt(v, u); siz[u] += siz[v];
        t = max(t, siz[v]);
    }
    t = max(t, sum - siz[u]);
    if (t < mn) mn = t, rt = u;
}
int getrt(int x) {
    sum = siz[x];
    mn = 1e9; rt = 0; 
    getrt(x, 0);
    return rt;
}

vector<int> dis; set<int> st;
void dfs(int u, int f, int d) {
    dis.push_back(d);
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == f || vis[v]) continue;
        dfs(v, u, d + x.second);
    }
}
void solve(int u) {
    vis[u] = 1; 
    st.clear(); st.insert(0);
    for (auto& x: edge[u]) {
        int v = x.first;
        if (vis[v]) continue;
        dis.clear();
        dfs(v, u, x.second);
        for (int i = 1; i <= q; i++) {
            if (ans[i]) continue;
            for (int& d: dis) if (que[i] >= d) ans[i] |= st.count(que[i] - d);
        }
        for (int& d: dis) st.insert(d);
    }
    for (auto& x: edge[u]) {
        int v = x.first;
        if (vis[v]) continue;
        solve(getrt(v));
    }
}

int main(){
    scanf("%d%d", &n, &q);
    for (int i = 2, u, v, w; i <= n; i++) {
        scanf("%d%d%d", &u, &v, &w);
        edge[u].push_back({v, w});
        edge[v].push_back({u, w});
    }
    for (int i = 1; i <= q; i++) scanf("%d", que + i);
    siz[1] = n; solve(getrt(1));
    for (int i = 1; i <= q; i++) if (ans[i]) puts("AYE"); else puts("NAY");
    return 0;
}