#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 300000 + 5;

vector<int> edge[maxn];
int n, m, id, vis[maxn], tag[maxn];

ll dfs(int u, int tp) {
    vis[u] = id;
    int nx = (tp == 1 ? 2 : 1); ll r = nx;
    for (int& v: edge[u]) {
        if (tag[v]) {
            if (tag[v] == tp) return 0;
            continue;
        }
        if (vis[v] == id) continue;
        // dbg(u, v);
        tag[v] = nx;
        r = r * dfs(v, nx) % mod;
        tag[v] = 0;
    }
    // dbg(u, r);
    return r;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) edge[i].clear(), vis[i] = 0;
        while (m--) {
            int u, v; scanf("%d%d", &u, &v);
            edge[u].push_back(v); edge[v].push_back(u);
        }
        ll ans = 1;
        for (int i = 1; i <= n; i++) if (!vis[i]) {
            // ans = ans * (dfs(i, 1) + dfs(i, 2)) % mod;
            ll tot = 0;
            id = tag[i] = 1; tot += dfs(i, 1); 
            // dbg(tot);
            // dbg('?');
            id = tag[i] = 2; tot += dfs(i, 2);
            tag[i] = 0;
            // dbg(tot);
            ans = ans * tot % mod;
        }
        printf("%I64d\n", ans);
    }
    return 0;
}