#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

vector<int> edge[maxn];
int n, k, key[maxn], deg[maxn];

int l[maxn], r[maxn];
void dfs(int u) {
    for (int& v: edge[u]) {
        dfs(v);
        // r[u] += r[v]; l[u] += l[v];
        if (key[u]) {
            r[u] = min(r[u], r[v]);
            if (l[u] == inf) l[u] = 0;
            l[u] += l[v];
        } else {
            if (r[u] == inf) r[u] = 0;
            r[u] += r[v];
            l[u] = max(l[u], l[v]);
        }
    }
    dbg(u, r[u]);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", key + i);
    for (int i = 2, f; i <= n; i++) {
        scanf("%d", &f); edge[f].push_back(i); deg[f]++;
    }
    for (int i = 1; i <= n; i++) if (deg[i] == 0) k++;
    for (int i = 1; i <= n; i++) if (deg[i] == 0) l[i] = 1, r[i] = 1; else r[i] = inf, l[i] = 0;
    dfs(1);
    cout << max(l[1], k - r[1] + 1);
    return 0;
}