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
const ll inf = 1ll << 60;
const int maxn = 100000 + 5;

int n, k, lc, pc, lm, pm, t, d, a[maxn];
ll sa[maxn], sb[maxn], sc[maxn], nb[maxn], nc[maxn];

int main() {
  scanf("%d%d%d%d%d%d%d%d", &n, &k, &lc, &pc, &lm, &pm, &t, &d);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  sort(a + 1, a + 1 + n);
  for (int i = 1; i <= n; i++) {
    sa[i] = min(a[i] - 1, d);
    if (a[i] >= lm) sb[i] = min(a[i] - lm, d);
    if (a[i] >= lc) sc[i] = min(a[i] - lc, d);
    if (a[i] < lm) nb[i] = lm - a[i];
    if (a[i] < lc) nc[i] = lc - a[i];
    sa[i] += sa[i - 1];
    sb[i] += sb[i - 1];
    sc[i] += sc[i - 1];
    nb[i] += nb[i - 1];
    nc[i] += nc[i - 1];
  }
  ll ans = inf;
  for (int i = 0; i <= n; i++) {
    ll pa = min((ll)i * (k - 1), (ll)n - i);
    if (i && a[n - i + 1] + d < lc) continue;
    if (a[pa + 1] + d < lm) continue;
    ll need = nc[n] - nc[n - i] + nb[n - i] - nb[pa];
    ll give = sc[n] - sc[n - i] + sb[n - i] - sb[pa] + sa[pa];
    if (need > give) continue;
    ans = min(ans, 1ll * i * pc + 1ll * (n - i - pa) * pm + need * t);
  }
  if (ans == inf) puts("-1");
  else printf("%I64d\n", ans);
  return 0;
}