#include <iostream>
#include <cstdio>
#include <cassert>
#include <vector>
#include <map>
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
using namespace std;
using ll = long long;
const int maxn = (1 << 20) + 5;

int n, m, q;
int state[maxn], cnt[21][maxn], dper[21][maxn];
vector<int> G[21];

int trans(int s) {
  int tot = 0;
  for (int i = 0; i < n; i++) {
    int sum = 0;
    for (int v: G[i]) {
      if (s >> v & 1) {
        sum++;
      }
    }
    if (sum % 2) {
      tot |= 1 << i;
    }
  }
  return tot;
}

int main() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 0, x; i < n; i++) {
    scanf("%d", &x);
    if (x) {
      state[0] |= 1 << i;
    }
  }
  for (int i = 0; i < n; i++) {
    cnt[i][0] = state[0] >> i & 1;
  }
  for (int i = 0, u, v; i < m; i++) {
    scanf("%d%d", &u, &v);
    u--; v--;
    G[v].push_back(u);
  }
  map<int,int> vis; vis[state[0]] = 0;
  int st = -1, per = -1;
  for (int i = 1; i <= (1 << n); i++) {
    state[i] = trans(state[i - 1]);
    for (int j = 0; j < n; j++) {
      cnt[j][i] = state[i] >> j & 1;
    }
    if (vis.count(state[i])) {
      st = vis[state[i]];
      per = i - st;
      break;
    } else {
      vis[state[i]] = i;
    }
  }
  assert(st != -1 && per != -1);
  for (int i = 0; i < n; i++) {
    for (int j = 1; j < st; j++) {
      cnt[i][j] += cnt[i][j - 1];
    }
  }
  for (int i = 0; i < n; i++) {
    dper[i][0] = cnt[i][st];
    for (int j = st + 1; j < st + per; j++) {
      dper[i][j - st] = dper[i][j - st - 1] + cnt[i][j];
    }
  }

  while (q--) {
    int x; ll k;
    scanf("%d%lld", &x, &k); x--;
    // 0 ~ st - 1
    int rk = lower_bound(cnt[x], cnt[x] + st, k) - cnt[x];
    if (rk < st) {
      assert(k >= cnt[x][rk]);
      printf("%d\n", rk);
    } else {
      k -= cnt[x][st - 1];
      assert(k > 0);
      if (dper[x][per - 1] == 0) {
        puts("-1"); continue;
      }
      // st ~ st + p - 1
      if (k % dper[x][per - 1] == 0) {
        ll ans = st + 1ll * (k / dper[x][per - 1] - 1) * per;
        k = dper[x][per - 1];
        int rk = lower_bound(dper[x], dper[x] + per, k) - dper[x];
        printf("%lld\n", ans + rk);
      } else {
        ll ans = st + 1ll * k / dper[x][per - 1] * per;
        k %= dper[x][per - 1];
        int rk = lower_bound(dper[x], dper[x] + per, k) - dper[x];
        printf("%lld\n", ans + rk);
      }
    }
  }
  return 0;
}