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

ll tr[maxn];
inline int lowbit(int x){return x & -x;}
inline void update(int i, int x){
    while (i < maxn) tr[i] += x, i += lowbit(i);
}
inline ll query(int i){
    ll r = 0; while (i) r += tr[i], i -= lowbit(i);
    return r;
}

vector<int> edge[maxn];
vector<PII> que[maxn];
int n, m, tot, in[maxn], out[maxn], dep[maxn];
ll ans[maxn];

void dfs1(int u, int f){
    dep[u] = dep[f] + 1;
    in[u] = ++tot; 
    for (auto& v : edge[u]){
        if (v == f) continue;
        dfs1(v, u);
    }
    out[u] = tot;
}
void dfs(int u, int f){
    for (auto& x : que[u]){
        update(dep[u], x.second);
        update(dep[u] + x.first + 1, -x.second);
    }
    ans[u] = query(dep[u]);
    for (auto& v : edge[u]){
        if (v == f) continue;
        dfs(v, u); 
    }
    for (auto& x : que[u]){
        update(dep[u], -x.second);
        update(dep[u] + x.first + 1, x.second);
    }
}

int main(){
    scanf("%d", &n);
    for (int i = 1, x, y; i < n; i++) {
        scanf("%d%d", &x, &y); 
        edge[x].push_back(y); edge[y].push_back(x);
    } dfs1(1, 0);
    scanf("%d", &m);
    while (m--){
        int v, d, x; scanf("%d%d%d", &v, &d, &x);
        que[v].push_back({d, x});
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) printf("%I64d ", ans[i]);
    return 0;
}