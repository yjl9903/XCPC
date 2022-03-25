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
#include <random>
#include <ctime>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, m, pre[maxn], deg[maxn];
vector<int> edge[maxn];

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}

int dis[maxn];
int bfs(int u) {
  for (int i = 1; i <= n; i++) {
    dis[i] = -1;
  }
  queue<int> q;
  dis[u] = 0;
  q.push(u);
  int mx = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    mx = max(mx, dis[u]);
    for (int v: edge[u]) {
      if (dis[v] == -1) {
        dis[v] = dis[u] + 1;
        q.push(v);
      }
    }
  }
  return mx;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    pre[i] = i;
  }
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
    deg[u]++;
    deg[v]++;
    int x = find(u), y = find(v);
    if (x != y) {
      pre[x] = y;
    }
  }
  for (int i = 1, rt = find(1); i <= n; i++) {
    if (find(i) != rt) {
      puts("-1");
      return 0;
    }
  }
  int ans = 0;
  if (n <= 10000) {
    for (int i = 1; i <= n; i++) {
      ans = max(ans, bfs(i));
    }
  } else {
    mt19937 rnd(time(nullptr));
    for (int i = 1, cnt = 0; i <= n && cnt <= 10; i++) {
      if (deg[i] == 1) {
        ans = max(ans, bfs(i));
        cnt++;
      }
    }
    for (int i = 1; i <= 100; i++) {
      ans = max(ans, bfs(i));
    }
  }
  int val = __lg(ans);
  if ((1 << val) == ans) {
    printf("%d\n", val);
  } else {
    printf("%d\n", val + 1);
  }
  return 0;
}