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
const int maxn = 20 + 5;

int getBit(int x, int b) {
  return x >> b & 1;
}

int n, a[maxn][maxn], col[maxn][maxn];
char s[maxn];

int dis[(1 << 24) + 5];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%s", s);
    for (int j = 0; j < n; j++) {
      if (s[j] == 'W') {
        col[i][j] = 1;
      } else if (s[j] == 'B') {
        col[i][j] = 2;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &a[i][j]);
    }
  }
  ms(dis, -1);
  int st = ((1 << n) - 1) << n, ed = (1 << n) - 1;
  dis[st] = 0;
  vector<int> corner;
  vector<int> ca, cc;
  for (int u = st; u >= ed; u--) {
    if (__builtin_popcount(u) != n) continue;
    if (dis[u] == -1) continue;
    int x = 0, y = 0;
    corner.clear();
    ca.clear();
    cc.clear();
    for (int i = 0; i + 1 < n + n; i++) {
      if (getBit(u, i) == 0 && getBit(u, i + 1) == 1) {
        if (col[x][y]) {
          corner.emplace_back(i);
          ca.push_back(a[x][y]);
          cc.push_back(col[x][y]);
        }
        int nxt = u ^ (1 << i) ^ (1 << (i + 1));
        int val = dis[u];
        if (col[x][y]) {
          val += a[x][y];
        }
        if (dis[nxt] == -1 || dis[nxt] > val) {
          dis[nxt] = val;
        }
      }
      if (getBit(u, i) == 0) {
        x++;
      } else {
        y++;
      }
    }
    for (int i = 0; i < corner.size(); i++) {
      for (int j = 0; j < i; j++) {
        if (cc[i] != cc[j]) {
          int nxt = u;
          nxt ^= (1 << corner[i]) ^ (1 << (corner[i] + 1));
          nxt ^= (1 << corner[j]) ^ (1 << (corner[j] + 1));
          int val = dis[u] + abs(ca[i] - ca[j]);
          if (dis[nxt] == -1 || dis[nxt] > val) {
            dis[nxt] = val;
          }
        }
      }
    }
  }
  printf("%d\n", dis[ed]);
  return 0;
}