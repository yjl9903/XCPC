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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

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

namespace pam {
  int sz, tot, last;
  int ch[maxn][26], len[maxn], fail[maxn];
  int cnt[maxn], fa[maxn];
  char s[maxn];
  int node(int l) {
    sz++; ms(ch[sz], 0);
    len[sz] = l; fail[sz] = cnt[sz] = 0;
    return sz;
  }
  void clear() {
    sz = -1; last = 0;
    s[tot = 0] = '$';
    node(0); node(-1);
    fail[0] = 1;
  }
  int getfail(int x) {
    while (s[tot - len[x] - 1] != s[tot]) x = fail[x];
    return x;
  }
  int insert(char c) {
    s[++tot] = c;
    int now = getfail(last);
    if (!ch[now][c - 'a']) {
      int x = node(len[now] + 2);
      fail[x] = ch[getfail(fail[now])][c - 'a'];
      ch[now][c - 'a'] = x;
      fa[x] = now;
    }
    last = ch[now][c - 'a'];
    cnt[last]++;
    return last;
  }
  void count() {
    for (int i = sz; i >= 0; i--) {
      cnt[fail[i]] += cnt[i];
    }
  }
}

char s[maxn];
int n, f[maxn], g[maxn], h[maxn];
bool vis[maxn];

void dfs(int u) {
  if (u <= 1) return ;
  if (vis[u]) return ;
  vis[u] = true;
  f[u] = 1;
  int f1 = pam::fa[u], f2 = pam::fail[u];
  dfs(f1); dfs(f2);
  f[u] = add(f[u], g[f1]);
  g[u] = add(f[u], g[f1]);
  g[u] = add(g[u], add(h[f2], h[f2]));
  h[u] = add(f[u], h[f2]);
}

int main() {
  pam::clear();
  scanf("%s", s + 1);
  n = strlen(s + 1);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int u = pam::insert(s[i]);
    dfs(u); ans = add(ans, h[u]);
  }
  cout << ans << endl;
  return 0;
}