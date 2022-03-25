#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

vector<int> edge[maxn];
int n, c[maxn];
ll ans[maxn], cnt[maxn];

int sz[maxn], son[maxn], in[maxn], out[maxn], id[maxn], tot;
void getsz(int u, int f){
    sz[u] = 1; 
    in[u] = ++tot; id[tot] = u;
    for (auto& v : edge[u]){
        if (v == f) continue;
        getsz(v, u); sz[u] += sz[v];
        if (sz[v] > sz[son[u]]){
            son[u] = v;
        }
    }
    out[u] = tot;
}
ll res = 0; int mx = 0; bool sk[maxn];
void add(int u, int f, int x){
    cnt[c[u]] += x;
    if (x > 0 && cnt[c[u]] >= mx){
        if (cnt[c[u]] > mx) res = 0, mx = cnt[c[u]];
        res += c[u];
    }
    for (auto& v : edge[u]){
        if (v == f || sk[v]) continue;
        add(v, u, x);
    }
}
void dfs(int u, int f, int kp){
    for (auto& v : edge[u]){
        if (v == f || v == son[u]) continue;
        dfs(v, u, 0);
    }
    if (son[u]) dfs(son[u], u, 1), sk[son[u]] = 1;

    add(u, f, 1);
    // cnt[c[u]]++;
    // if (cnt[c[u]] == mx) res += c[u];
    // if (cnt[c[u]] > mx) res = c[u];
    // for (auto& v : edge[u]){
    //     if (v == f || v == son[u]) continue;
    //     for (int i = in[v]; i <= out[v]; i++){
    //         cnt[c[id[i]]]++;
    //         if (cnt[c[id[i]]] >= mx){
    //             if (cnt[c[id[i]]] > mx) res = 0, mx = cnt[c[id[i]]];
    //             res += c[id[i]];
    //         }
    //     }
    // }
    
    ans[u] = res;

    // if (!kp){
    //     res = mx = 0;
    //     for (int i = in[u]; i <= out[u]; i++){
    //         cnt[c[id[i]]]--;
    //     }
    // }
    if (son[u]) sk[son[u]] = 0;
    if (!kp) add(u, f, -1), res = mx = 0;
}

int main(){
    scanf("%d", &n); for (int i = 1; i <= n; i++) scanf("%d", c + i);
    for (int i = 1; i < n; i++){
        int x, y; scanf("%d%d", &x, &y);
        edge[x].push_back(y); edge[y].push_back(x);
    }
    getsz(1, 0); dfs(1, 0, 0);
    for (int i = 1; i <= n; i++) printf("%I64d ", ans[i]);
    return 0;
}