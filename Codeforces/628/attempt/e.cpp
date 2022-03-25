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
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 25;
const int maxn = 500000 + 5;

namespace sieve{
  const int maxp = 1000000 + 5;
  int vis[maxp], prime[maxp], id[maxp], tot;
  void init() {
    ms(vis, 0);
    for (int i = 2; i < maxp; i++) {
      if (!vis[i]) prime[tot++] = i;
      for (int j = 0; j < tot && prime[j] * i < maxp; j++) {
        vis[i * prime[j]] = 1;
        if (i % prime[j] == 0) break;
      }
    }
    for (int i = 0; i < tot; i++) {
      id[prime[i]] = i;
    }
  }
}
using sieve::tot;
using sieve::prime;
using sieve::id;

int n, a[maxn], key[maxn], tag[200][200];

vector<int> edge[maxn];
int dis[maxn];
void bfs(int s) {
  for (int i = 0; i < tot; i++) {
    dis[i] = inf;
  }
  dis[s] = 0; queue<int> q; q.push(s);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v: edge[u]) {
      if (u < 200 && v < 200 && tag[u][v]) continue;
      if (dis[v] > dis[u] + 1) {
        dis[v] = dis[u] + 1;
        q.push(v);
      }
    }
  }
}

int main() {
  sieve::init();
  scanf("%d", &n);
  map<int,int> mp1; map<PII,int> mp2;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    int x = a[i];
    vector<int> v;
    for (int i = 0; prime[i] * prime[i] <= x; i++) {
      if (x % prime[i]) continue;
      int c = 0;
      while (x % prime[i] == 0) x /= prime[i], c++;
      if (c % 2) v.push_back(prime[i]);
    }
    if (x > 1) v.push_back(x);
    if (v.empty()) {
      puts("1"); return 0;
    } else if ((int)v.size() == 1) {
      mp1[v[0]]++;
    } else if ((int)v.size() == 2) {
      mp2[{v[0], v[1]}]++;
    } else {
      assert(false);
    }
  }
  for (auto& x: mp1) {
    if (x.second > 1) {
      puts("2"); return 0;
    }
    key[id[x.first]] = 1;
  }
  for (auto& x: mp2) {
    if (x.second > 1) {
      puts("2"); return 0;
    }
    int a = id[x.first.first], b = id[x.first.second];
    edge[a].push_back(b); edge[b].push_back(a);
  }
  for (int i = 0; i < tot; i++) {
    sort(begin(edge[i]), end(edge[i]));
  }
  int ans = inf;
  for (int i = 0; prime[i] < 1000; i++) {
    for (int v: edge[i]) {
      if (v > i) break;
      tag[i][v] = tag[v][i] = true;
      bfs(i);
      ans = min(ans, dis[v] + 1);
      tag[i][v] = tag[v][i] = false;
    }
    bfs(i);
    int mn = inf, mn2 = inf;
    for (int i = 0; i < tot; i++) {
      if (!key[i]) continue;
      if (dis[i] <= mn) {
        mn2 = mn;
        mn = dis[i];
      } else if (dis[i] <= mn2) {
        mn2 = dis[i];
      }
    }
    ans = min(ans, mn + mn2 + 2);
  }
  if (ans == inf) puts("-1");
  else printf("%d\n", ans);
  return 0;
}