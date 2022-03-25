#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 100000 + 5;

int n, q, a[maxn];
vector<int> edge[maxn];

int tot, fa[maxn][20], rdfn[maxn], tin[maxn], tout[maxn];
void dfs(int u, int f) {
  tin[u] = ++tot;
  rdfn[tot] = u;
  fa[u][0] = f;
  for (int j = 1; j < 20; j++) {
    fa[u][j] = fa[fa[u][j - 1]][j - 1];
  }
  for (int v : edge[u]) {
    if (v == f) continue;
    dfs(v, u);
  }
  tout[u] = tot;
}

struct Event {
  int x, y, op, id;

  bool operator<(const Event& other) const { return x < other.x; }
};

int ans[maxn], c[maxn];
void update(int i, int x) {
  for (i++; i < maxn; i += i & -i) c[i] += x;
}
int query(int i) {
  int r = 0;
  for (i++; i; i -= i & -i) r += c[i];
  return r;
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    int fa;
    scanf("%d%d", a + i, &fa);
    if (i == 1) continue;
    edge[fa].push_back(i);
    edge[i].push_back(fa);
  }
  dfs(1, 0);
  vector<Event> evs;
  for (int i = 1; i <= q; i++) {
    int o, L, R;
    scanf("%d%d%d", &o, &L, &R);
    for (int j = 19; j >= 0; j--) {
      if (fa[o][j] && a[fa[o][j]] <= R) {
        o = fa[o][j];
      }
    }
    evs.push_back({tin[o], L, 1, i});
    evs.push_back({tin[o], R + 1, -1, i});
    evs.push_back({tout[o] + 1, L, -1, i});
    evs.push_back({tout[o] + 1, R + 1, 1, i});
  }
  sort(evs.begin(), evs.end());
  for (int i = 1, j = 0; i <= n; i++) {
    while (j < evs.size() && evs[j].x <= i) {
      update(evs[j].y, evs[j].op);
      j++;
    }
    ans[rdfn[i]] = query(a[rdfn[i]]);
  }
  for (int i = 1; i <= n; i++) {
    printf("%d ", ans[i]);
  }
  return 0;
}