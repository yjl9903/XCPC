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

int n;
ll f[maxn];
vector<int> eds[maxn];
PII a[maxn];

int main() {
  scanf("%d", &n);
  ll sumc = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].first, &a[i].second);
    sumc += a[i].second;
  }
  sort(a + 1, a + 1 + n);
  multiset<pair<ll,int> > st;
  ll cur = 0;
  for (int i = 1; i <= n; i++) {
    if (i > 1) {
      cur += a[i].first - a[i - 1].first;
    }
    for (auto x: eds[i]) {
      st.erase(st.find({ f[x], x }));
      cur = min(cur, f[x] + a[i].first - a[x].first - a[x].second);
    }
    f[i] = cur;
    if (!st.empty()) {
      f[i] = min(f[i], st.begin()->first);
    }
    dbg(i, f[i]);
    int right = lower_bound(a + 1, a + 1 + n, PII { a[i].first + a[i].second, -1 }) - a;
    dbg(right);
    if (right > i) {
      st.emplace(f[i], i);
      eds[right].push_back(i);
    }
  }
  printf("%lld\n", sumc + f[n]);
  return 0;
}