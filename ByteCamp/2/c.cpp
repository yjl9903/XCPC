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

inline int add(int x, int y) {
  x += y;
  return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
  x -= y;
  return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
  return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
  int r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x % mod;
    n >>= 1; x = 1ll * x * x % mod;
  }
  return r;
}
inline int inv(int x) {
  return qpow(x, mod - 2);
}

int n, l, p;
char s[maxn];

bool check(ll x){
  return __builtin_popcountll(x) <= p;
}

struct Trie {
  static const int maxs = 2500000 + 5;
  int sz, val[maxs];
  vector<PII> ch[maxs];
  
  void clear() {
    sz = 0; node();
  }
  int node() {
    int u = ++sz;
    ch[u].clear(); val[u] = 0;
    return u;
  }

  void insert(ll state, int x) {
    int u = 1;
    while (state) {
      int pos = __builtin_ffsll(state);
      // if (!ch[u].count(pos)) {
      //   ch[u][pos] = node();
      // }
      int v = -1;
      for (auto& x: ch[u]) {
        if (x.first == pos) {
          v = x.second;
          break;
        }
      }
      if (v == -1) {
        v = node();
        ch[u].push_back({ pos, v });
      }
      u = v;
      // u = ch[u][pos];
      state >>= pos;
    }
    val[u] = add(val[u], x);
  }
  int query() {
    int ans = 0;
    for (int i = 1; i <= sz; i++) {
      ans = add(ans, val[i]);
    }
    return ans;
  }
} ds[2];

int main() {
  ds[0].clear(); ds[1].clear();
  scanf("%d%d%d", &n, &l, &p);
  scanf("%s", s + 1);
  int f = 0;
  ds[0].insert(0, 1);
  for (int i = 1; i <= n; i++, f ^= 1) {
    ds[f ^ 1].clear();
    function<void(int,int,ll)> dfs = [&](int u, int len, ll state) {
      if (ds[f].val[u] != 0) {
        ll x = state;
        if (x >> (l - 1) & 1) x ^= 1ll << (l - 1);
        x <<= 1;
        for (int j = 0; j < 2; j++) {
          if (s[i] == '*' || s[i] - '0' == j) {
            if (check(x | j)) {
              ds[f ^ 1].insert(x | j, ds[f].val[u]);
            }
          }
        }
      }
      for (const PII& x: ds[f].ch[u]) {
        int pos = x.first, v = x.second;
        dfs(v, len + pos, state | (1ll << (len + pos - 1)));
      }
    };
    dfs(1, 0, 0);
  }
  printf("%d\n", ds[f].query());
  return 0;
}