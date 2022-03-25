#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <map>
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
const int maxn = 200000 + 5;
const int maxv = 5032107 + 5;

namespace Factor {
  const int maxp = 5032107 + 5;
  int vis[maxp], prime[maxp], pcnt;
  int mdiv[maxp], ndiv[maxp];
  void init() {
    for (int i = 2; i < maxp; i++) {
      if (!vis[i]) prime[pcnt++] = i, mdiv[i] = i;
      for (int j = 0; j < pcnt && prime[j] * i < maxp; j++) {
        vis[i * prime[j]] = 1;
        mdiv[i * prime[j]] = prime[j];
        if (i % prime[j] == 0) break;
      }
    }
    for (int i = 2; i < maxp; i++) {
      int p = mdiv[i];
      int cur = i / mdiv[i];
      if (cur % p == 0) ndiv[i] = ndiv[cur];
      else ndiv[i] = ndiv[cur] + 1;
    }
  }
  int norm(int x) {
    int tot = 1;
    for (int i = 0; i < pcnt && 1ll * prime[i] * prime[i] <= x; i++) {
      if (x % prime[i]) continue;
      int c = 0;
      while (x % prime[i] == 0) c++, x /= prime[i];
      if (c % 2) tot *= prime[i];
    }
    if (x > 1) tot *= x;
    return tot;
  }
  vector<int> getFactor(int x) {
    int tot = x;
    vector<int> v;
    for (int i = 1; 1ll * i * i <= tot; i++) {
      if (tot % i) continue;
      v.push_back(i);
      if (1ll * i * i != tot) v.push_back(tot / i);
    }
    return v;
  }
}
using Factor::ndiv;

int n, q, a[maxn], ans[1049659];
int dp[maxv][8], best[30];
vector<PII> que[maxn];

int main() {
  Factor::init();
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 1, l, r; i <= q; i++) {
    scanf("%d%d", &l, &r);
    que[r].emplace_back(l, i);
  }
  for (int i = 1; i <= n; i++) {
    a[i] = Factor::norm(a[i]);
    auto divs = Factor::getFactor(a[i]);
    for (auto& d: divs) {
      int tot = ndiv[a[i]] - ndiv[d];
      for (int i = 0; i <= 7; i++) {
        best[i + tot] = max(best[i + tot], dp[d][i]);
      }
    }
    for (auto& q: que[i]) {
      int le = q.first, id = q.second;
      ans[id] = -1;
      for (int i = 0; i <= 14; i++) {
        if (best[i] >= le) {
          ans[id] = i; break;
        }
      }
      assert(ans[id] != -1);
    }
    for (auto& d: divs) {
      int ad = ndiv[a[i]] - ndiv[d];
      dp[d][ad] = max(dp[d][ad], i);
    }
  }
  for (int i = 1; i <= q; i++) printf("%d\r\n", ans[i]);
  return 0;
}