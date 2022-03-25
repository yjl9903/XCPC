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
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300 + 5;

int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int n, a[maxn][maxn], k, dis[maxn][maxn], vis[maxn][maxn];
char s[maxn];

struct Node {
  int x, y, d;
  bool operator<(const Node& b) const {
    return d > b.d;
  }
};

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s + 1);
    for (int j = 1; j <= n; j++) {
      a[i][j] = s[j] - '0';
      dis[i][j] = inf;
    }
  }
  priority_queue<Node> pq;
  scanf("%d", &k);
  for (int i = 1, x, y; i <= k; i++) {
    scanf("%d%d", &x, &y);
    pq.push({x, y, 0});
    dis[x][y] = 0;
  }
  while (!pq.empty()) {
    auto tp = pq.top(); pq.pop();
    if (vis[tp.x][tp.y]) continue;
    vis[tp.x][tp.y] = 1;
    for (int i = 0; i < 4; i++) {
      int x = tp.x + dir[i][0];
      int y = tp.y + dir[i][1];
      if (x < 1 || y < 1 || x > n || y > n) continue;
      if (vis[x][y]) continue;
      if (dis[x][y] > dis[tp.x][tp.y] + a[tp.x][tp.y]) {
        dis[x][y] = dis[tp.x][tp.y] + a[tp.x][tp.y];
        pq.push({x, y, dis[x][y]});
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      ans = max(ans, dis[i][j] + a[i][j]);
    }
  }
  cout << ans;
  return 0;
}