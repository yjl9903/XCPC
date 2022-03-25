#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 2000 + 5;

vector<int> edge[maxn], st;
int n, m, id, cnt, dfn[maxn], low[maxn], vis[maxn], bel[maxn];

void init(){
    id = cnt = 0; ms(dfn, 0); ms(vis, 0);
    for (int i = 0; i < 2 * n; i++) edge[i].clear();
    st.clear();
}

void dfs(int u){
    dfn[u] = low[u] = ++id;
    vis[u] = 1; st.push_back(u);
    for (auto& v : edge[u]){
        if (!dfn[v]){
            dfs(v); low[u] = min(low[u], low[v]);
        }
        else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]){
        int t; cnt++;
        do{
            t = st.back(); st.pop_back();
            bel[t] = cnt; vis[t] = 0;
        }while(t != u);
    }
}

int main(){
    while (~scanf("%d%d", &n, &m)){
        init();
        while (m--){
            int a1, a2, c1, c2; scanf("%d%d%d%d", &a1, &a2, &c1, &c2);
            edge[2 * a1 + c1].push_back(2 * a2 + 1 - c2);
            edge[2 * a2 + c2].push_back(2 * a1 + 1 - c1);
        }
        for (int i = 0; i < 2 * n; i++) if (!dfn[i]) dfs(i);
        int flag = 1;
        for (int i = 0; i < 2 * n && flag; i += 2){
            if (bel[i] == bel[i + 1]) flag = 0;
        }
        if (flag) puts("YES");
        else puts("NO");
    }
    return 0;
}