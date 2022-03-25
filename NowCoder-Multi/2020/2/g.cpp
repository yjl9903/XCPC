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
#include <bitset>
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
const int maxm = 5 + 5;

int n, m, a[maxn], b[maxn], pos[maxn], aid[maxn], bid[maxn];
bitset<maxm> cur, ok[maxm];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    aid[i] = i;
  }
  for (int i = 1; i <= m; i++) {
    scanf("%d", b + i);
    bid[i] = i;
  }
  sort(aid + 1, aid + 1 + n, [&](int lhs, int rhs) { return a[lhs] < a[rhs]; });
  sort(bid + 1, bid + 1 + m, [&](int lhs, int rhs) { return b[lhs] < b[rhs]; });
  for (int i = 1, j = 1, tot = 0; i <= n; i++) {
    bool flag = false;
    while (j <= m && b[bid[j]] <= a[aid[i]]) {
      if (!flag) {
        flag = true;
        tot++;
        ok[tot] = ok[tot - 1];
      }
      ok[tot].set(bid[j]);
      j++;
    }
    pos[aid[i]] = tot;
    // dbg(aid[i], a[aid[i]], tot, ok[tot]);
  }
  cur.set(0);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    cur <<= 1;
    cur &= ok[pos[i]];
    cur.set(0);
    dbg(i, cur);
    if (cur.test(m)) {
      ans++;
    }
  }
  cout << ans << endl;
  return 0;
}