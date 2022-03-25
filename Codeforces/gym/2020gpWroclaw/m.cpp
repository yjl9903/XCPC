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
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, p, q;
PII a[maxn];
ll b[maxn], pre[maxn], tag[maxn];

bool check(int x) {
  for (int i = x; i <= n; i++) {
    ll sum = pre[i] - pre[i - x];
    if (1ll * a[i].first * q * x <= 1ll * p * sum) {
      return true;
    }
  }
  return false;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i].first);
      a[i].second = i;
      tag[i] = 0;
    }
    scanf("%d%d", &p, &q);
    sort(a + 1, a + 1 + n);
    tag[0] = tag[n + 1] = 0;
    pre[0] = 0;
    for (int i = 1; i <= n; i++) {
      pre[i] = pre[i - 1] + a[i].first;
      b[i] = 1ll * p * a[i].first;
    }
    int l = 1, r = n, ans = -1;
    while (l <= r) {
      int m = (l + r) / 2;
      if (check(m)) {
        ans = m;
        l = m + 1;
      } else {
        r = m - 1;
      }
    }
    dbg(ans);
    assert(ans != -1);
    for (int i = ans; i <= n; i++) {
      ll sum = pre[i] - pre[i - ans];
      if (1ll * a[i].first * q * ans <= 1ll * p * sum) {
        tag[i - ans + 1]++;
        tag[i + 1]--;
        if (ans > 1) {
          ll cur = 1ll * q * a[i].first * ans - 1ll * p * (sum - a[i - ans + 1].first);
          int id = lower_bound(b + 1, b + 1 + n, cur) - b;
          // dbg(i, id,  cur);
          assert(id <= i - ans + 1);
          tag[id]++;
          tag[i - ans + 1]--;
        }
      }
    }
    vector<int> vec;
    for (int i = 1; i <= n; i++) {
      tag[i] += tag[i - 1];
      if (!tag[i]) {
        vec.push_back(a[i].second);
      }
    }
    sort(vec.begin(), vec.end());
    printf("%d\n", vec.size());
    for (int i = 0; i < vec.size(); i++) {
      // if (i > 0) putchar(' ');
      printf("%d%c", vec[i], " \n"[i + 1 == vec.size()]);
    }
    puts("");
  }
  return 0;
}