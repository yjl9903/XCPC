#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 20000 + 5;

vector<int> edge[maxn], st;
int n, m, id, cnt, dfn[maxn], low[maxn], vis[maxn], bel[maxn], ind[maxn], oud[maxn];

void init(){
    for (int i = 1; i <= n; i++) edge[i].clear(); st.clear();
    ms(dfn, 0); ms(vis, 0); ms(ind, 0); ms(oud, 0);
    id = cnt = 0;
}

void dfs(int u){
    dfn[u] = low[u] = ++id;
    vis[u] = 1; st.push_back(u);
    for (auto& v : edge[u]){
        if (!dfn[v]) {
            dfs(v); low[u] = min(low[u], low[v]);
        }
        else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]){
        int t; cnt++;
        do {
            t = st.back(); st.pop_back();
            vis[t] = 0; bel[t] = cnt;
        } while (t != u);
    }
}

int main(){
    while (~scanf("%d%d", &n, &m)){
        init();
        while (m--){   
            int x, y; scanf("%d%d", &x, &y);
            edge[x].push_back(y);
        }
        for (int i = 1; i <= n; i++) if (!dfn[i]) dfs(i);
        for (int i = 1; i <= n; i++) for (auto& v : edge[i]){
            if (bel[v] == bel[i]) continue;
            oud[bel[i]]++; ind[bel[v]]++;
        }
        int t1 = 0, t2 = 0;
        for (int i = 1; i <= cnt; i++) {
            if (!ind[i]) t1++;
            if (!oud[i]) t2++;
        }
        printf("%d\n", cnt <= 1 ? 0 : max(t1, t2));
    }
    return 0;
}