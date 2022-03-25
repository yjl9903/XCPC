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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, m;
vector<int> edge[2][maxn];

struct Node {
  static const int L = 19;
  
  int u, g, rev, dis;

  bool operator<(const Node& rhs) const {
    if (rev >= L && rhs.rev >= L) {
      if (rev == rhs.rev) return dis < rhs.dis;
      return rev < rhs.rev;
    } else if (rev >= L) {
      return false;
    } else if (rhs.rev >= L) {
      return true;
    } else {
      return dis + (1 << rev) < rhs.dis + (1 << rhs.rev);
    }
  }

  bool operator>(const Node& rhs) const {
    return rhs < *this;
  }

  int eval() {
    int r = 1;
    for (int i = 0; i < rev; i++) r = 2ll * r % mod;
    r--;
    if (r == -1) r += mod;
    r = (r + dis) % mod;
    return r;
  }
} dis[maxn][2][20];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    edge[0][u].push_back(v);
    edge[1][v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 20; k++) {
        dis[i][j][k] = Node { i, j, inf, inf };
      }
    }
  }
  priority_queue<Node, vector<Node>, greater<Node> > pq;
  dis[1][0][0] = Node { 1, 0, 0, 0 };
  pq.push(dis[1][0][0]);
  while (!pq.empty()) {
    auto tp = pq.top();
    pq.pop();
    {
      Node nx { tp.u, tp.g ^ 1, tp.rev + 1, tp.dis };
      if (dis[tp.u][tp.g ^ 1][min(19, tp.rev + 1)] > nx) {
        dis[tp.u][tp.g ^ 1][min(19, tp.rev + 1)] = nx;
        pq.push(nx);
      }
    }
    for (int v: edge[tp.g][tp.u]) {
      Node nx { v, tp.g, tp.rev, tp.dis + 1 };
      if (dis[v][tp.g][min(19, tp.rev)] > nx) {
        dis[v][tp.g][min(19, tp.rev)] = nx;
        pq.push(nx);
      }
    }
  }
  auto ans = dis[n][0][0];
  for (int j = 0; j < 2; j++) {
    for (int k = 0; k < 20; k++) {
      ans = min(ans, dis[n][j][k]);
    }
  }
  printf("%d\n", ans.eval());
  return 0;
}