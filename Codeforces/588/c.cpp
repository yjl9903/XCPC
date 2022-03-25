#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <set>
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
const int maxn = 100000 + 5;

int n, m, q, deg[maxn];
vector<int> ein[maxn];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v);
        deg[u]++; deg[v]++;
        if (u < v) swap(u, v);
        ein[v].push_back(u);
    }
    auto cal = [&](int u) {
        return 1ll * (int)ein[u].size() * (deg[u] - (int)ein[u].size());
    };
    ll ans = 0;
    for (int i = 1; i <= n; i++) ans += cal(i);
    printf("%I64d\n", ans);
    scanf("%d", &q);
    for (int i = 1, x; i <= q; i++) {
        scanf("%d", &x);
        ans -= cal(x);
        for (int& v: ein[x]) {
            ans -= cal(v);
            ein[v].push_back(x);
            ans += cal(v);
        }
        ein[x].clear();
        printf("%I64d\n", ans);
    }
    return 0;
}