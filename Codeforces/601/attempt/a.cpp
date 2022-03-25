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
const int maxn = 100 + 5;

char gc(int x) {
  if (x < 26) return x + 'a';
  else if (x < 52) return x - 26 + 'A';
  else return x - 52 + '0';
  return '.';
}

int r, c, k, vis[maxn][maxn];
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
char s[maxn][maxn], ans[maxn][maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &r, &c, &k);
    int sum = 0;
    for (int i = 1; i <= r; i++) {
      scanf("%s", s[i] + 1);
      for (int j = 1; j <= c; j++) {
        if (s[i][j] == 'R') sum++;
        vis[i][j] = 0;
      }
    }
    vector<int> num(k, sum / k);
    for (int i = sum / k * k + 1, j = 0; i <= sum; i++, j++) {
      num[j]++;
    }
    for (int i = 0; i < k; i++) {
      int cnt = 0;
      queue<PII> q;
      for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
          if (!vis[i][j]) {
            q.emplace(i, j);
            break;
          }
        }
      }
      while (!q.empty()) {
        PII tp = q.front(); q.pop();
        int x = tp.first, y = tp.second;
        if (vis[x][y]) continue;
        vis[x][y] = 1;
        ans[x][y] = gc(i);
        if (s[x][y] == 'R') cnt++;
        if (i + 1 < k && cnt == num[i]) break;
        for (int i = 0; i < 4; i++) {
          int tx = x + dir[i][0];
          int ty = y + dir[i][1];
          if (tx < 1 || tx > r || ty < 1 || ty > c) continue;
          q.emplace(tx, ty);
        }
      }
    }
    for (int i = 1; i <= r; i++) {
      for (int j = 1; j <= c; j++) {
        putchar(ans[i][j]);
      }
      puts("");
    }
  }
  return 0;
}