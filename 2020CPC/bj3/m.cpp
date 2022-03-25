#include <cstdio>
#include <functional>
#include <utility>
#include <vector>
#include <queue>
using namespace std;
using PII = pair<int,int>;
const int maxn = 200000 + 5;

int n, siz[maxn], son[maxn];
int tot, L[maxn], R[maxn], rdfn[maxn];
vector<int> edge[maxn];

void getsz(int u) {
  L[u] = ++tot;
  rdfn[tot] = u;
  siz[u] = 1;
  for (int v: edge[u]) {
    getsz(v);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) {
      son[u] = v;
    }
  }
  R[u] = tot;
}

int push(int u) {
  putchar('+');
  printf("%d", u);
  return 1;
}
int pushTree(int u) {
  for (int i = L[u]; i <= R[u]; i++) {
    push(rdfn[i]);
  }
  return R[u] - L[u] + 1;
}
void pop(int len = 1) {
  while (len--) {
    putchar('-');
  }
}
void ok(int u) {
  putchar('=');
  printf("%d", u);
}

void solve(int u) {
  int sz = 0;
  for (int x = u; x; x = son[x]) {
    ok(x);
    sz += push(x);
    for (int v: edge[x]) {
      if (v == son[x]) continue;
      sz += pushTree(v);
    }
  }
  priority_queue<PII, vector<PII>, greater<PII> > pq;
  for (int x = u; x; x = son[x]) {
    for (int v: edge[x]) {
      if (v == son[x]) continue;
      pq.emplace(siz[v], v);
    }
  }
  if (pq.empty()) return ;
  pop(sz);
  vector<PII> ch;
  while (pq.size() >= 2) {
    auto x = pq.top(); pq.pop();
    auto y = pq.top(); pq.pop();
    if (x.first > y.first) swap(x, y);
    ch.emplace_back(x.second, y.second);
    pq.emplace(x.first + y.first, ch.size() + n);
  }
  function<int(int)> add = [&](int u) {
    if (u <= n) {
      return pushTree(u);
    } else {
      u -= n + 1;
      return add(ch[u].first) + add(ch[u].second);
    }
  };
  function<int(int)> dfs = [&](int u) {
    if (u <= n) {
      solve(u);
      return siz[u];
    } else {
      u -= n + 1;
      int sz = add(ch[u].second);
      sz += dfs(ch[u].first);
      pop(sz);
      add(ch[u].first);
      dfs(ch[u].second);
      return sz;
    }
  };
  for (int x = u; x; x = son[x]) {
    push(x);
  }
  dfs(pq.top().second);
}

int main() {
  scanf("%d", &n);
  int x = __lg(n);
  for (int i = 2; i <= n; i++) {
    int fa;
    scanf("%d", &fa);
    edge[fa].push_back(i);
  }
  getsz(1);
  solve(1);
  puts("!");
  return 0;
}