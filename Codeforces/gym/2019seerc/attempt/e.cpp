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

ll fun(int a, int b, int c) {
  int used = (a + k - 2) / (k - 1);
  ll ans = 1ll * used * pc;
  c -= used;
  int sum = b + c - (used * (k - 1) - a);
  if (sum <= 0) return ans;
  ll res = 1ll * sum * pm;
  int r = min(c, (sum + k - 1) / k);
  res = min(res, 1ll * sum * pm + 1ll * r * (pc - 1ll * k * pm));
  return ans + res;
}

int main() {
  scanf("%d%d%d%d%d%d%d%d", &n, &k, &lc, &pc, &lm, &pm, &t, &d);
  vector<int> va, vb, vc;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i); 
    if (a[i] < lm) va.push_back(a[i]);
    else if (a[i] < lc) vb.push_back(a[i]);
    else vc.push_back(a[i]);
  }
  if (k == 1) {
    if ((int)va.size() > 0) return puts("-1"), 0;
    ll ans = 1ll * n * pm;
    int r = min((int)vc.size(), (n + k - 1) / k);
    ans = min(ans, 1ll * r * (pc - 1ll * k * pm) + 1ll * n * pm);
    printf("%I64d\n", ans);
    return 0;
  }
  if (((int)va.size() + k - 2) / (k - 1) <= (int)vc.size()) {
    ll ans = fun((int)va.size(), (int)vb.size(), (int)vc.size());
    printf("%I64d\n", ans);
  } else {
    sort(va.begin(), va.end());
    sort(vb.begin(), vb.end());
    sort(vc.begin(), vc.end());
    sort(a + 1, a + 1 + n);
    auto solve1 = [&]() -> ll {
      int mx = (k - 1) * (int)vc.size();
      ll sum = 0;
      for (int x: vc) sum += min(x - lc, d);
      for (int x: vb) sum += min(x - lm, d);
      for (int i = 0; i < mx; i++) {
        sum += min(va[i] - 1, d);
      }
      ll res = 0;
      for (int i = mx; i < (int)va.size(); i++) {
        int x = va[i];
        if (lm - x > d) {
          return inf;
        } else {
          sum -= lm - x;
          res += lm - x;
        }
        if (sum < 0) {
          return inf;
        }
      }
      int a = mx, b = (int)vb.size() + (int)va.size() - mx, c = (int)vc.size();
      return fun(a, b, c) + res * t;
    };
    auto solve2 = [&]() -> ll {
      int mn = ((int)va.size() + k - 2) / (k - 1);
      ll sum = 0; int ff = 0;
      for (int x: vc) sum += min(x - lc, d);
      // for (int i = 0; i < (int)vb.size() - mn)
      for (int i = 1; i <= n - mn; i++) {
        if (a[i] < lm) {
          sum += min(a[i] - 1, d);
        } else {
          sum += min(a[i] - lm, d);
        }
      }
      ll res = 0;
      for (int i = n - mn + 1; i <= n; i++) {
        if (a[i] >= lc) break;
        if (lc - a[i] > d) {
          return inf;
        } else {
          sum -= lc - a[i];
          res += lc - a[i];
        }
        if (sum < 0) {
          return inf;
        }
      }
      int c = mn, b = max(0, (int)vb.size() - mn);
      return fun(n - b - c, b, c) + res * t;
    };
    ll ans = min(solve1(), solve2());
    if (ans == inf) puts("-1");
    else {
      printf("%I64d\n", ans);
    }
  }
  return 0;
}