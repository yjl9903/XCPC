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
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, q, tot, tin[maxn], tout[maxn];
vector<int> edge[maxn];

int cnt, root[maxn], ls[maxn * 40], rs[maxn * 40];
ll tree[maxn * 40];
void update(int L, int R, int x, int pre, int l, int r, int& rt) {
  rt = ++cnt; ls[rt] = ls[pre]; rs[rt] = rs[pre];
  tree[rt] = tree[pre] + x;
  if (l == r) return;
  int m = (l + r) >> 1;
  if (L <= m) update(L, R, x, ls[pre], lson);
  if (R > m) update(L, R, x, rs[pre], rson);
}
ll query(int u, int pre, int l, int r, int rt) {
  if (l == r) return tree[rt] - tree[pre];
  int m = (l + r) / 2;
  if (u <= m) return query(u, ls[pre], lson);
  else return query(u, rs[pre], rson);
}

map<string,int> id;
map<int,int> created;
int getID(const string& s) {
  if (id.count(s)) {
    return id[s];
  } else {
    return id[s] = id.size() + 1;
  }
}
map<int,vector< pair<int,ll> > > csum;
ll query(int u, int r) {
  auto it = upper_bound(begin(csum[u]), end(csum[u]), make_pair(r, (ll)1e18));
  if (it == begin(csum[u])) return 0;
  it--;
  // dbg(it->first, it->second);
  return it->second;
}

void dfs(int u) {
  tin[u] = ++tot;
  for (int v: edge[u]) {
    dfs(v);
  }
  tout[u] = tot;
}

int main() {
  scanf("%d", &n);
  vector<tuple<int,int,int> > evs;
  for (int i = 1; i <= n; i++) {
    char cmd[20], id[20];
    scanf("%s%s", cmd, id);
    if (cmd[0] == 'n') {
      edge[0].push_back(getID(id));
      created[getID(id)] = i;
    } else if (cmd[0] == 'c') {
      int val; scanf("%d", &val);
      evs.emplace_back(i, getID(id), val);
      int u = getID(id);
      ll last = val;
      if (!csum[u].empty()) last += csum[u].back().second;
      csum[u].emplace_back(i, last);
    } else if (cmd[0] == 'b') {
      char id2[20];
      scanf("%s", id2);
      edge[getID(id)].push_back(getID(id2));
      created[getID(id2)] = i;
    }
  }
  dfs(0);
  for (int i = 1, p = 0; i <= n && p < (int)evs.size(); i++) {
    if (i == get<0>(evs[p])) {
      int t, u, v; tie(t, u, v) = evs[p];
      update(tin[u], tout[u], v, root[i - 1], 1, n, root[i]);
      p++;
    } else {
      root[i] = root[i - 1];
    }
  }
  scanf("%d", &q);
  while (q--) {
    int l, r;
    char id[20];
    scanf("%d%d%s", &l, &r, id);
    if (!::id.count(id)) {
      puts("0");
    } else {
      int u = getID(id);
      int cTime = created[u];
      ll ans = 0;
      if (l >= cTime) {
        printf("%lld\n", query(u, r) - query(u, l - 1));
        continue;
      }
      if (r >= cTime) {
        // ans += query(u, r);
        r = cTime;
      }
      ans += query(tin[u], root[l - 1], 1, n, root[r]);
      printf("%lld\n", ans);
    }
  }
  return 0;
}