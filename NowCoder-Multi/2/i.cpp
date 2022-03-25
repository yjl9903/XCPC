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
const int inf = 1 << 30;
const int maxn = 20 + 5;

int n = 20;
bool A[25][25], B[25][25];
bool C[25][25], D[25][25];
char buf[128];
int pre[21][21][21][21];
int dis[21][21][21][21];

const vector< pair<PII, PII> > trans {
  { { 1, 0 }, { 1, 0 } },
  { { 0, -1 }, { 0, 1 } },
  { { 0, 1 }, { 0, -1 } },
  { { -1, 0 }, { -1, 0 } }
};

struct State {
  PII a, b;
  int dir;

  bool check() {
    if (a.first <= 0 || a.first > 20 || a.second <= 0 || a.second > 20) return false;
    if (b.first <= 0 || b.first > 20 || b.second <= 0 || b.second > 20) return false;
    if (!A[a.first][a.second]) return false;
    if (!B[b.first][b.second]) return false;
    return dis[a.first][a.second][b.first][b.second] == -1;
  }

  State go(int i) {
    PII na { a.first + trans[i].first.first, a.second + trans[i].first.second };
    if (na.first <= 0 || na.first > 20 || na.second <= 0 || na.second > 20 || !A[na.first][na.second]) {
      na = PII { a.first, a.second };
    }
    PII nb { b.first + trans[i].second.first, b.second + trans[i].second.second };
    if (nb.first <= 0 || nb.first > 20 || nb.second <= 0 || nb.second > 20 || !B[nb.first][nb.second]) {
      nb = PII { b.first, b.second };
    }
    return State { na, nb, i };
  }
};

int main() {
  for (int i = 1; i <= n; i++) {
    scanf("%s", buf + 1);
    for (int j = 1; j <= n; j++) {
      A[i][j] = buf[j] == '.' ? true : false;
    }
    scanf("%s", buf + 1);
    for (int j = 1; j <= n; j++) {
      B[i][j] = buf[j] == '.' ? true : false;
    }
  }

  ms(pre, -1);
  ms(dis, -1);
  queue<State> q;
  q.push({ { 20, 20 }, { 20, 1 }, -1 });
  dis[20][20][20][1] = 0;
  while (!q.empty()) {
    auto u = q.front();
    if (u.a == PII { 1, 20 } && u.b == PII { 1, 1 }) break;
    q.pop();
    for (int i = 0; i < 4; i++) {
      auto nxt = u.go(i);
      if (!nxt.check()) continue;
      assert(nxt.a != u.a || nxt.b != u.b);
      pre[nxt.a.first][nxt.a.second][nxt.b.first][nxt.b.second] = i;
      if (nxt.a != u.a) {
        pre[nxt.a.first][nxt.a.second][nxt.b.first][nxt.b.second] |= 8;
      }
      if (nxt.b != u.b) {
        pre[nxt.a.first][nxt.a.second][nxt.b.first][nxt.b.second] |= 16;
      }
      dis[nxt.a.first][nxt.a.second][nxt.b.first][nxt.b.second] = dis[u.a.first][u.a.second][u.b.first][u.b.second] + 1;
      q.push(nxt);
    }
  }

  string cmd;
  int x1 = 1, y1 = 20, x2 = 1, y2 = 1;
  C[x1][y1] = true;
  D[x2][y2] = true;
  while (pre[x1][y1][x2][y2] >= 0) {
    int d = pre[x1][y1][x2][y2];
    cmd += "DLRU"[d & 3];
    if (d & 8) {
      x1 -= trans[d & 3].first.first;
      y1 -= trans[d & 3].first.second;
    }
    if (d & 16) {
      x2 -= trans[d & 3].second.first;
      y2 -= trans[d & 3].second.second;
    }
    C[x1][y1] = true;
    D[x2][y2] = true;
  }
  reverse(cmd.begin(), cmd.end());
  printf("%d\n", cmd.length());
  puts(cmd.c_str());
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (!A[i][j]) putchar('#');
      else if (C[i][j]) putchar('A');
      else putchar('.');
    }
    putchar(' ');
    for (int j = 1; j <= n; j++) {
      if (!B[i][j]) putchar('#');
      else if (D[i][j]) putchar('A');
      else putchar('.');
    }
    puts("");
  }
  return 0;
}