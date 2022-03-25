#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
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
const int maxn = 200000 + 5;

int n;
vector<PII> edge[maxn];

ll ans;
struct DSU {
    int pre[maxn], siz[maxn];
    int find(int x) {
        return x == pre[x] ? x : pre[x] = find(pre[x]);
    }
    void join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return ;
        pre[x] = y; siz[y] += siz[x];
    }
    int check(int x, int y) {
        return find(x) == find(y);
    }
    void init(int n) {
        for (int i = 1; i <= n; i++) pre[i] = i, siz[i] = 1;
    }
    ll cal() {
        ll ans = 0;
        for (int i = 1; i <= n; i++) if (i == pre[i]) {
            ans += 1ll * siz[i] * (siz[i] - 1);
        }
        return ans;
    }
    int size(int u) {
        return siz[find(u)];
    }
} f[2];

int main() {
    scanf("%d", &n);
    f[0].init(n); f[1].init(n);
    for (int i = 2, u, v, w; i <= n; i++) {
        scanf("%d%d%d", &u, &v, &w);
        f[w].join(u, v);
    }
    ans = f[0].cal() + f[1].cal();
    dbg(ans);
    for (int i = 1; i <= n; i++) {
        if (f[0].size(i) > 1 && f[1].size(i) > 1) {
            ans += 1ll * (f[0].size(i) - 1) * (f[1].size(i) - 1);
            dbg(i, f[0].size(i) - 1, f[1].size(i) - 1);
        }
    }
    cout << ans << endl;
    return 0;
}