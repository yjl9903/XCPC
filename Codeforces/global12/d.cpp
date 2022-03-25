#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
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
const int maxn = 300000 + 5;

int n, a[maxn], dfn[maxn], R[maxn], L[maxn];
bool ans[maxn];

struct BIT {
  int a[maxn];
  void clear() {
    for (int i = 0; i <= n; i++) a[i] = 0;
  }
  void update(int i, int x) {
    for (; i <= n; i += i & -i) a[i] += x;
  }
  int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += a[i];
    return r;
  }
} f;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      dfn[i] = inf;
    }
    vector<int> stk;
    for (int i = 1; i <= n; i++) {
      while (!stk.empty() && a[stk.back()] > a[i]) {
        R[stk.back()] = i;
        stk.pop_back();
      }
      stk.push_back(i);
    }
    while (!stk.empty()) {
      R[stk.back()] = n + 1;
      stk.pop_back();
    }
    for (int i = n; i >= 1; i--) {
      while (!stk.empty() && a[stk.back()] > a[i]) {
        L[stk.back()] = i;
        stk.pop_back();
      }
      stk.push_back(i);
    }
    while (!stk.empty()) {
      L[stk.back()] = 0;
      stk.pop_back();
    }
    for (int i = 1; i <= n; i++) {
      dfn[a[i]] = min(dfn[a[i]], R[i] - L[i] - 1);
    }
    f.clear();
    vector<PII> evs;
    for (int i = 1; i <= n; i++) {
      if (dfn[i] != inf) {
        evs.emplace_back(dfn[i], i);
      }
    }
    sort(evs.begin(), evs.end(), greater<PII>());
    for (int i = n, cnt = 0, p = 0; i >= 1; i--) {
      while (p < evs.size() && evs[p].first == i) {
        f.update(evs[p].second, 1);
        p++;
      }
      if (f.query(n - i + 1) == n - i + 1) {
        ans[i] = true;
      } else {
        ans[i] = false;
      }
    }
    for (int i = 1; i <= n; i++) {
      putchar(ans[i] + '0');
    }
    puts("");
  }
  return 0;
}