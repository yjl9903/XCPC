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
const int maxn = 100000 + 5;

int m, n, a[maxn], b[maxn];
int pre[maxn];
set<int> A[maxn];

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
  x = find(x);
  y = find(y);
  if (x != y) {
    pre[x] = y;
  }
}

int main() {
  scanf("%d%d", &m, &n);
  for (int i = 1; i <= m; i++) {
    scanf("%d", a + i);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", b + i);
    pre[i] = i;
  }
  ll ans = 0;
  set<tuple<ll,int,int> > st;
  for (int i = 1; i <= m; i++) {
    int k, x;
    scanf("%d", &k);
    while (k--) {
      scanf("%d", &x);
      ans -= a[i] + b[x];
      // A[i].insert(x);
      st.emplace(a[i] + b[x], i, x);
    }
  }
  while (!st.empty()) {
    auto mx = *st.rbegin();
    ll tot = get<0>(mx);
    int aid = get<1>(mx);
    int val = get<2>(mx);
    st.erase(--st.end());

    bool flag = true;
    int L = -1, R = -1;
    auto it = A[aid].upper_bound(val);
    if (it != A[aid].end()) {
      if (find(val) == find(*it)) {
        flag = false;
      } else {
        R = *it;
      }
    }
    if (it != A[aid].begin()) {
      it--;
      if (find(val) == find(*it)) {
        flag = false;
      } else {
        L = *it;
      }
    }

    if (flag) {
      A[aid].insert(val);
      ans += tot;
      if (L != -1) join(L, val);
      if (R != -1) join(val, R);
    }
  }

  printf("%I64d\n", -ans);
  return 0;
}