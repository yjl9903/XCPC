#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
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
typedef pair<int,ll> PII;
const int mod = 998244353;
const int maxn = 200000 + 5;

vector<PII> edge[maxn];
int n, m, uu[maxn], vv[maxn], deg[maxn];
ll a[maxn], ww[maxn];
ll ans[maxn], dp[maxn];

void dfs(int u) {
    dp[u] = a[u];
    for (auto& x: edge[u]) {
        dfs(x.first);
        dp[u] = min(dp[u], dp[x.first] + 2ll * x.second);
    }
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++) {
        ll w; scanf("%d%d%I64d", uu + i, vv + i, ww + i);
        edge[u].push_back({v, w * 2});
        edge[v].push_back({u, w * 2});
    }
    for (int i = 1; i <= n; i++) {
        scanf("%I64d", a + i);
    }
    for (int i = 1; i <= m; i++) {
        if (a[uu[i]] < a[vv[i]]) {
            edge[vv[i]].push_back({uu[i], ww[i]});
            deg[uu[i]]++;
        }
        if (a[uu[i]] > a[vv[i]]) {
            edge[uu[i]].push_back({vv[i], ww[i]});
            deg[vv[i]]++;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (deg[i]) continue;
        dfs(i);
    }
    for (int i = 1; i <= n; i++) printf("%I64d ", dp[i]);
    return 0;
}