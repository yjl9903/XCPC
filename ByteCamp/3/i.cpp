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
const int maxn = 3000 + 5;

namespace hk {
  int n, ans;
  int dx[maxn], dy[maxn];
  int linkx[maxn], linky[maxn];
  int head[maxn], to[maxn * maxn], nxt[maxn * maxn], ecnt;

  void clear(int N) {
    n = N; ecnt = ans = 0;
    ms(linkx, 0xff); ms(linky, 0xff); ms(head, 0);
  }
  void adde(int u, int v) {
    to[++ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt;
    if (linkx[u] == -1 && linky[v] == -1) {
      linkx[u] = v;
      linky[v] = u;
      ans++;
    }
  }
  bool bfs() {
    bool res = 0;
    static int q[maxn], l, r;

    ms(dx, 0); ms(dy, 0);
    l = r = 0;
    for (int i = 1; i <= n; i++)
      if (linkx[i] == -1) q[r++] = i;

    while (l < r) {
      int x = q[l++];
      for (int i = head[x]; i; i = nxt[i]) {
        if (!dy[to[i]]) {
          dy[to[i]] = dx[x] + 1;
          if (linky[to[i]] == -1) res = 1;
          else dx[q[r++] = linky[to[i]]] = dy[to[i]] + 1;
        }
      }
    }
    return res;
  }
  bool dfs(int u) {
    for (int i = head[u]; i; i = nxt[i]) {
      if (dx[u] + 1 == dy[to[i]]) {
        dy[to[i]] = 0;
        if (linky[to[i]] == -1 || dfs(linky[to[i]])) {
          linky[to[i]] = u;
          linkx[u] = to[i];
          return true;
        }
      }
    }
    return false;
  }
  int match(int n) {
    // clear(n): 1 ~ n
    while (bfs()) {
      for (int i = 1; i <= n; i++) {
        if (linkx[i] == -1) ans += dfs(i);
      }
    }
    return ans;
  }
}

int L, n, a[maxn], b[maxn];

map<ll, int> pos2id;
int getId(ll pos) {
  if (pos2id.count(pos)) {
    return pos2id[pos];
  } else {
    return -1;
  }
}

int nxt[maxn][2], cnt[maxn];
bool solve(ll t, int sk) {
  // dbg(t, sk);
  hk::clear(n); ms(cnt, 0);
  set<PII> st; set<int> stOne;
  for (int i = 2; i <= n; i++) {
    int le = getId(a[i] + t);
    int ri = getId(a[i] - t);
    if (le == -1 && ri == -1) {
      return false;
    }
    if (le > ri) swap(le, ri);
    if (st.count({ le, ri })) {
      return false;
    }
    st.insert({ le, ri });
    nxt[i][0] = le; nxt[i][1] = ri;
    if (le != -1 && le != sk) {
      cnt[le]++;
      hk::adde(i, le);
    }
    if (ri != -1 && ri != sk) {
      if (le == -1) {
        if (stOne.count(ri)) {
          return false;
        }
        stOne.insert(ri);
      }
      cnt[ri]++;
      hk::adde(i, ri);
    }
  }
  for (int i = 1; i <= n; i++) {
    if (i != sk && cnt[i] == 0) return false;
  }
  for (auto& x: st) {
    if (stOne.count(x.first) && stOne.count(x.second)) {
      return false;
    }
  }
  return hk::match(n) == n - 1;
}

int main() {
  scanf("%d%d", &L, &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  vector<pair<ll,int> > allD;
  for (int i = 1; i <= n; i++) {
    scanf("%d", b + i);
    allD.emplace_back(b[i], i);
    allD.emplace_back(L + L - b[i] + 1, i);
    allD.emplace_back(-b[i] + 1, i);
    pos2id[b[i]] = i;
    pos2id[L + L - b[i] + 1] = i;
    pos2id[-b[i] + 1] = i;
  }
  assert(pos2id.size() == 3 * n);
  ll ans = 2ll * L + 1;
  for (auto& x: allD) {
    ll t = abs(a[1] - x.first);
    if (t < ans && solve(t, x.second)) {
      ans = t;
    }
  }
  if (ans == 2ll * L + 1) {
    puts("-1");
  } else {
    printf("%lld\n", ans);
  }
  return 0;
}