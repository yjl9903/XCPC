#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

vector<int> edge[maxn], st;
int n, id, dfn[maxn], low[maxn], vis[maxn];
int cnt, bel[maxn], ind[maxn], oud[maxn];

void dfs(int u){
    dfn[u] = low[u] = ++id;
    vis[u] = 1; st.push_back(u);
    for (int i = 0; i < edge[u].size(); i++){
        int v = edge[u][i];
        if (!dfn[v]){
            dfs(v); low[u] = min(low[u], low[v]);
        }
        else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]){
        cnt++; int t = 0;
        do{
            t = st.back(); st.pop_back();
            bel[t] = cnt;
            vis[t] = 0;
        } while(t != u);
    }
}

int main(){
    while (~scanf("%d", &n)){
        ms(dfn, 0); ms(vis, 0); st.clear(); cnt = id = 0;
        for (int i = 1; i <= n; i++){
            int x; edge[i].clear();
            while (scanf("%d", &x) && x){
                edge[i].push_back(x);
            }
        }
        for (int i = 1; i <= n; i++) if (!dfn[i]) dfs(i);
        ms(ind, 0); ms(oud, 0);
        for (int i = 1; i <= n; i++){
            dbg(bel[i]);
        }
        for (int i = 1; i <= n; i++) for (int j = 0; j < edge[i].size(); j++){
            int x = edge[i][j];
            if (bel[i] == bel[x]) continue;
            oud[bel[i]]++; ind[bel[x]]++;
        }
        int t1 = 0, t2 = 0;
        for (int i = 1; i <= cnt; i++){
            dbg(ind[i], oud[i]);
            if (!ind[i]) t1++;
            if (!oud[i]) t2++;
        }
        if (cnt <= 1) printf("1\n0\n");
        else printf("%d\n%d\n", t1, max(t1, t2));
    }
    return 0;
}