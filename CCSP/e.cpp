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
const int maxn = 2000 + 5;

int dis(PII a, PII b){
    int x = a.first - b.first, y = a.second - b.second;
    return abs(x) + abs(y);
}

int n, a, b, dis1[maxn], dis2[maxn];
PII s1, s2, hate[maxn], like[maxn];
vector<int> edge[maxn], st;

int id, dfn[maxn], low[maxn], vis[maxn], cnt, bel[maxn];
void init(int x){
    for (int i = 1; i <= 2 * n; i++) edge[i].clear();
    int d = dis(s1, s2);
    for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) {
        if (dis2[i] + dis2[j] > x){
            edge[i + n].push_back(j); edge[j + n].push_back(i);
        }
        if (dis1[i] + dis1[j] > x){
            edge[i].push_back(j + n); edge[j].push_back(i + n);
        }
        if (dis2[i] + dis1[j] + d > x){
            edge[i + n].push_back(j + n); edge[j].push_back(i);
        }
        if (dis1[i] + dis2[j] + d > x){
            edge[i].push_back(j); edge[j + n].push_back(i + n);
        }
    }
    for (int i = 0; i < a; i++){
        edge[hate[i].first].push_back(hate[i].second + n);
        edge[hate[i].first + n].push_back(hate[i].second);
        edge[hate[i].second].push_back(hate[i].first + n);
        edge[hate[i].second + n].push_back(hate[i].first);
    }
    for (int i = 0; i < b; i++){
        edge[like[i].first + n].push_back(like[i].second + n);
        edge[like[i].first].push_back(like[i].second);
        edge[like[i].second + n].push_back(like[i].first + n);
        edge[like[i].second].push_back(like[i].first);
    }
    ms(dfn, 0); ms(vis, 0); st.clear(); cnt = id = 0; 
}

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

int check(int x){
    init(x);
    // cout << x << endl;
    for (int i = 1; i <= 2 * n; i++) if (!dfn[i]) dfs(i);
    for (int i = 1; i <= n; i++) if (bel[i] == bel[i + n]) return false;
    return true;
}

int main(){
    ios::sync_with_stdio(false); 
    while (~scanf("%d%d%d%d%d%d%d", &n, &a, &b, &s1.first, &s1.second, &s2.first, &s2.second)){
        for (int i = 1; i <= n; i++){
            int x, y; scanf("%d%d", &x, &y);
            dis1[i] = dis({x, y}, s1); dis2[i] = dis({x, y}, s2);
        }

        for (int i = 0; i < a; i++) scanf("%d%d", &hate[i].first, &hate[i].second);
        for (int i = 0; i < b; i++) scanf("%d%d", &like[i].first, &like[i].second);

        int l = 1, r = 1e8, ans = -1;
        while (l <= r){
            int m = l + r >> 1;
            if (check(m)) r = m - 1, ans = m;
            else l = m + 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}