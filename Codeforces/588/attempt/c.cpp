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

int n, m, q, a[maxn];
set<int> ein[maxn], eout[maxn];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) a[i] = i;
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v);
        if (u < v) swap(u, v);
        ein[v].insert(u);
        eout[u].insert(v);
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += 1ll * (int)ein[i].size() * (int)eout[i].size();
    }
    printf("%I64d\n", ans);
    scanf("%d", &q);
    for (int i = 1, x; i <= q; i++) {
        scanf("%d", &x);
        a[x] = n + i;
        ans -= 1ll * (int)ein[x].size() * (int)eout[x].size();
        set<int> tmp;
        for (auto it = eout[x].begin(); it != eout[x].end(); ) {
            dbg(1, *it);
            if (a[x] > a[*it]) it++;
            else {
                auto it2 = it; it2++;
                int v = *it; tmp.insert(v);
                ein[v].erase(x);
                ans -= (int)eout[v].size();
                eout[v].insert(x);
                ans += (int)ein[v].size();
                eout[x].erase(it);
                it = it2;
            }
        }
        for (auto it = ein[x].begin(); it != ein[x].end(); ) {
            dbg(2, *it);
            if (a[x] < a[*it]) it++;
            else {
                auto it2 = it; it2++;
                int v = *it; eout[x].insert(v);
                eout[v].erase(x);
                ans -= (int)ein[v].size();
                ein[v].insert(x);
                ans += (int)eout[v].size();
                ein[x].erase(it);
                it = it2;
            }
        }
        for (auto& y: tmp) ein[x].insert(y);

        ans += 1ll * (int)ein[x].size() * (int)eout[x].size();
        printf("%I64d\n", ans);
    }
    return 0;
}