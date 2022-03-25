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
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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
const int maxn = 1000000 + 5;

struct DSU {
  int pre[maxn];
  void init(int n) {
    for (int i = 0; i <= n; i++) pre[i] = i;
  }
  int find(int x) {
    return x == pre[x] ? x : pre[x] = find(pre[x]);
  }
  bool join(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return 0;
    pre[x] = y;
    return 1;
  }
} f;

int t, a, c, m, vis[maxn];
int dep[maxn], fa[maxn], onRing[maxn];
vector<int> edge[maxn];

int nxt(int x) {
  return (1ll * a * x + c) % m;
}

vector<int> ring;
void dfs(int u) {
  vis[u] = true;
  for (int v: edge[u]) {
    if (vis[v]) {
      if (!ring.empty()) continue;
      int x = u;
      while (x != v) {
        onRing[x] = true;
        ring.push_back(x);
        x = fa[x];
      }
      ring.push_back(v);
      onRing[v] = true;
      continue;
    }
    fa[v] = u;
    dfs(v);
  }
  vis[u] = false;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &t, &a, &c, &m);
    f.init(m);
    for (int i = 0; i < m; i++) {
      vis[i] = onRing[i] = false;
      fa[i] = dep[i] = 0;
      edge[i].clear();
    }
    vector<int> roots;
    for (int i = 0; i < m; i++) {
      edge[nxt(i)].push_back(i);
      if (!f.join(i, nxt(i))) {
        roots.push_back(i);
      }
    }
    ll ans = 0;
    for (int x: roots) {
      fa[x] = 0;
      ring.clear();
      dfs(x);
      int len = ring.size();
      vector<int> pre(len + len);
      for (int i = 0; i < len + len; i++) {
        if (i >= 2) {
          pre[i] = pre[i - 2];
        }
        pre[i] += ring[i % len] % 2 == 0;
      }

      auto cal = [&](int st, int l) -> ll {
        if (len == 1) {
          return 1ll * (l + 1) * (ring.front() % 2 == 0);
        }
        int p = st >= 2 ? pre[st - 2] : 0;
        int R = st + l * 2;
        ll ans = 0;
        if (R >= len + len) {
          int per = 0;
          if (R % 2 == (len + len - 1) % 2) {
            per = pre[len + len - 1];
          } else {
            per = pre[len + len - 2];
          }
          int cnt = (R + len + len - 1) / (len + len);
          assert(cnt >= 1);
          ans += 1ll * per * (cnt - 1);
          R = R % (len + len);
          if (R == 0) ans += per;
        }
        return pre[R] + ans - p;
      };

      auto getLen = [&](int x) -> PII {
        if (t + t < x) return { -1, -1 };
        int R = min(x, t), L = x - R;
        if (L > R) swap(L, R);
        return { (R - L) % 2, (R - L) / 2 };
      };

      auto bruteforce = [&](int u, PII tot) {
        if (tot.first == -1) return 0;
        if (tot.first == 1) u = nxt(u);
        int ans = u % 2 == 0, len = tot.second;
        while (len--) {
          u = nxt(nxt(u));
          ans += u % 2 == 0;
        }
        if (tot.first) {
          return ans + ans;
        } else {
          return ans + ans - 1;
        }
      };

      // dbg(x, ring.size());
      // for (int x: ring) dbg(x);

      for (int i = 0; i < len; i++) {
        int rt = ring[i];

        auto tot = getLen(rt);
        if (tot.first != -1) {
          if (tot.first) {
            ll cur = cal(i + 1, tot.second);
            ans += cur + cur;
            // dbg(cur + cur, bf);
          } else {
            ll cur = cal(i, tot.second);
            ans += cur + cur - 1;
            dbg(cur + cur - 1, ring[i]);
            // dbg(cur + cur - 1, bf);
          }
        }

        vector<int> stk;
        function<void(int)> dfs = [&](int u) {
          if (stk.size() <= 1) {
            stk.push_back(u % 2 == 0);
          } else {
            int cur = u % 2 == 0;
            cur += stk[(int)stk.size() - 2];
            stk.push_back(cur);
          }

          auto tot = getLen(u);
          if (tot.first != -1) {
            int d = dep[u] - tot.first;
            ll cur = 0;
            if (d >= tot.second * 2) {
              cur = stk[d];
              int top = d - tot.second * 2 - 2;
              cur -= top >= 0 ? stk[top] : 0;
            } else {
              cur = d >= 0 ? stk[d] : 0;
              if (d < 0) {
                assert(d == -1);
                cur += cal((i + 1) % len, tot.second - 1);
              } else if (d % 2) {
                cur += cal(i, tot.second - (d + 1) / 2);
              } else {
                cur += cal((i + 1) % len, tot.second - d / 2 - 1);
              }
            }
            if (tot.first) {
              cur += cur;
            } else {
              cur += cur - 1;
            }
            // dbg(u, cur, bruteforce(u, tot));
            ans += cur;
          }

          for (int v: edge[u]) {
            if (onRing[v]) continue;
            dep[v] = dep[u] + 1;
            dfs(v);
          }
          stk.pop_back();
        };

        for (int v: edge[rt]) {
          if (onRing[v]) continue;
          dep[v] = 0;
          dfs(v);
        }
      }
    }
    ll fm = (t + 1) * (t + 1);
    dbg(ans, fm);
    ll g = __gcd(fm, ans);
    printf("%lld/%lld\n", ans / g, fm / g);
  }
  return 0;
}