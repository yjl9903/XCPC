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

int n, k, a[maxn], cnt[maxn];
ll sum, f[maxn], g[maxn];

void add(int x) {
  sum += cnt[x];
  cnt[x]++;
}
void del(int x) {
  cnt[x]--;
  sum -= cnt[x];
}

void dfs(int l, int r, int L, int R) {
  if (l > r) return ;
  int m = (l + r) / 2;
  int pos = 1e9;
  ll val = 1e18;
  for (int i = l; i <= m; i++) {
    add(a[i]);
  }
  for (int i = L; i <= min(R, m); i++) {
    del(a[i]);
    ll cur = f[i] + sum;
    if (cur < val) {
      val = cur;
      pos = i;
    }
  }
  dbg(m, pos, val);
  g[m] = val;
  for (int i = L; i <= min(R, m); i++) {
    add(a[i]);
  }
  for (int i = l; i <= m; i++) {
    del(a[i]);
  }
  dfs(l, m - 1, L, pos);
  for (int i = L; i < pos; i++) {
    del(a[i]);
  }
  for (int i = l; i <= m; i++) {
    add(a[i]);
  }
  dfs(m + 1, r, pos, R);
  for (int i = L; i < pos; i++) {
    add(a[i]);
  }
  for (int i = l; i <= m; i++) {
    del(a[i]);
  }
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 1; i <= n; i++) {
    f[i] = f[i - 1] + cnt[a[i]];
    cnt[a[i]]++;
  }
  for (int i = 2; i <= k; i++) {
    ms(cnt, 0);
    sum = 0;
    dfs(1, n, 1, n);
    swap(f, g);
    // dbg(i);
    // for (int i = 1; i <= n; i++) {dbg(i, f[i]);}
  }
  printf("%lld\n", f[n]);
  return 0;
}