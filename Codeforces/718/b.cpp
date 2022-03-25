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
const int inf = 1 << 30;
const int maxn = 100 + 5;

struct Node {
  int x, y, val;

  bool operator < (const Node& b) {
    if (val == b.val) {
      if (x == b.x) {
        return y < b.y;
      }
      return x < b.x;
    }
    return val < b.val;
  }
};

int n, m, b[maxn][maxn], used[maxn];
bool vis[maxn][maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    vector<Node> vec;
    for (int i = 1; i <= n; i++) {
      used[i] = m;
      for (int j = 1; j <= m; j++) {
        scanf("%d", &b[i][j]);
        vis[i][j] = false;
      }
      sort(b[i] + 1, b[i] + 1 + m);
      for (int j = 1; j <= m; j++) {
        vec.push_back({ i, j, b[i][j] });
      }
    }
    sort(vec.begin(), vec.end());
    int p = 0;
    vector<vector<int> > ans;
    for (int i = 1; i <= m; i++) {
      while (p < vec.size() && vis[vec[p].x][vec[p].y] == 1) {
        p++;
      }
      int cx = vec[p].x, cy = vec[p].y;
      vector<int> cur;
      for (int j = 1; j <= n; j++) {
        if (j == cx) {
          vis[j][cy] = true;
          cur.push_back(b[cx][cy]);
        } else {
          cur.push_back(b[j][used[j]]);
          vis[j][used[j]] = true;
          used[j]--;
        }
      }
      ans.push_back(cur);
    }
    dbg("?", ans.size());
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        printf("%d%c", ans[j][i], " \n"[j + 1 == m]);
      }
    }
  }
  return 0;
}