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
const int maxn = 500000 + 5;

int n, a[maxn], nxt[maxn];
vector<PII> evs[maxn];

struct Bit {
  int n, a[maxn];
  void build(int nn) {
    n = nn;
    for (int i = 0; i <= n + 1; i++) {
      a[i] = 0;
    }
  }
  void update(int i, int x) {
    for (i++; i <= n + 1; i += i & -i) a[i] = max(a[i], x);
  }
  int query(int i) {
    int r = 0;
    for (i++; i; i -= i & -i) r = max(r, a[i]);
    return r;
  }
} f;

int solve(int n) {
  for (int i = 0; i <= n; i++) {
    evs[i].clear();
  }
  vector<int> stk;
  for (int i = 1; i <= n; i++) {
    while (!stk.empty() && a[stk.back()] <= a[i]) {
      nxt[stk.back()] = i;
      stk.pop_back();
    }
    stk.push_back(i);
  }
  while (!stk.empty()) {
    nxt[stk.back()] = n + 1;
    stk.pop_back();
  }
  f.build(n);
  for (int i = 1; i <= n; i++) {
    int val = f.query(a[i]);
    f.update(a[i], 1 + val);
    if (nxt[i] <= n) {
      evs[nxt[i]].emplace_back(a[i], 2 + val);
    }
    for (auto& ev: evs[i]) {
      f.update(ev.first, ev.second);
    }
  }
  return f.query(n);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    int ans1 = solve(n);
    for (int i = n; i >= 1; i--) {
      a[i + 1] = a[i];
    }
    a[1] = 1;
    int ans2 = solve(n + 1) - 1;
    printf("%d\n", max(ans1, ans2));
  }
  return 0;
}