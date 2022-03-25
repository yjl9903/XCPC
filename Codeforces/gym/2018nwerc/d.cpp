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
#include <queue>
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
using PII = pair<ll,int>;
const int mod = 998244353;
const ll inf = 1ll << 60;
const int maxn = 200000 + 5;

ll A, B;
int n, m, to[maxn], w[maxn];
vector<int> G[maxn], rG[maxn];

bool vis[maxn];
ll disS[maxn], disT[maxn];
void dij(int s, ll dis[], vector<int> edge[]) {
  ms(vis, false);
  for (int i = 1; i <= n; i++) dis[i] = inf;
  priority_queue<PII> pq;
  pq.emplace(0ll, s);
  dis[s] = 0;
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    if (vis[u]) continue;
    vis[u] = true;
    for (int i: edge[u]) {
      int v = to[i], w = ::w[i];
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        pq.emplace(-dis[v], v);
      }
    }
  }
}

ll last[maxn];
int deg[maxn];
bool keyP[maxn], keyE[maxn];
bool check(ll delta) {
  ms(deg, 0);
  ms(keyP, false);
  ms(keyE, false);
  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (disS[i] + disT[i] <= A + delta) {
      keyP[i] = true;
      q.push(i);
    }
  }
  if (q.empty()) return false;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i: G[u]) {
      int v = to[i], w = ::w[i];
      if (w + disT[v] <= delta) {
        keyE[i] = true;
        deg[v]++;
        if (!keyP[v]) {
          keyP[v] = true;
          q.push(v);
        }
      }
    }
  }
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (keyP[i]) {
      cnt++;
      last[i] = A + delta - disT[i];
      if (!deg[i]) {
        q.push(i);
      }
    }
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    cnt--;
    if (last[u] >= B) return true;
    for (int i: G[u]) {
      int v = to[i], w = ::w[i];
      if (!keyE[i]) continue;
      if (!keyP[v]) continue;
      last[v] = max(last[v], last[u] + w);
      deg[v]--;
      if (deg[v] == 0) q.push(v);
    }
  }
  return cnt > 0;
}

int main() {
  scanf("%I64d%I64d%d%d", &A, &B, &n, &m);
  for (int i = 1; i <= m; i++) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    to[i + i - 1] = b;
    w[i + i - 1] = c;
    to[i + i] = a;
    w[i + i] = c;
    G[a].push_back(i + i - 1);
    rG[b].push_back(i + i);
  }
  dij(1, disS, G);
  dij(n, disT, rG);
  for (int i = 1; i <= n; i++) {
    dbg(i, disS[i], disT[i]);
  }
  ll l = 0, r = disT[1] - 1, ans = disT[1];
  while (l <= r) {
    ll m = (l + r) / 2;
    if (check(m)) {
      ans = m;
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  cout << ans << endl;
  return 0;
}