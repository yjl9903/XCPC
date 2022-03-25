#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, c[maxn], vis[maxn]; 
vector<int> edge[maxn];

ll ans;
ll cal(int x) {
    return 1ll * x * (x - 1) / 2;
}

int sum, siz[maxn], cnt[maxn];
void dfs(int u, int ff) {
    siz[u] = 1;
    int lastc = cnt[c[u]], last = lastc;
    int lasts = ++sum;

    for (int v: edge[u]) {
        if (v == ff) continue;
        dfs(v, u);
        siz[u] += siz[v];

        ans -= cal((sum - lasts) - (cnt[c[u]] - last));
        // dbg(sum - lasts - cnt[c[u]] + last);

        last = cnt[c[u]];
        lasts = sum;
    }

    cnt[c[u]] = lastc + siz[u];
}

int main() {
    int kase = 0;
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; i++) {
            vis[i] = cnt[i] = 0;
            edge[i].clear();
        }
        int kinds = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", c + i);
            vis[c[i]]++; if (vis[c[i]] == 1) kinds++;
        }
        for (int i = 2, u, v; i <= n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        ans = 1ll * cal(n) * kinds;
        dfs(1, 0);
        // dbg(ans);
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) continue;
            ans -= cal(n - cnt[i]);
        }
        printf("Case #%d: %I64d\n", ++kase, ans);        
    }
    return 0;
}