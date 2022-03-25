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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500 + 5;

const vector<PII> dir = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

int n, m, a[maxn][maxn], b[maxn][maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        scanf("%d", &a[i][j]);
        b[i][j] = 0;
      }
    }
    bool isNo = false;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        for (auto d: dir) {
          int x = i + d.first;
          int y = j + d.second;
          if (x < 1 || y < 1 || x > n || y > m) continue;
          b[x][y]++;
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (a[i][j] > b[i][j]) {
          isNo = true;
        }
      }
    }
    if (isNo) {
      puts("NO");
    } else {
      puts("YES");
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
          printf("%d ", b[i][j]);
        }
        puts("");
      }
    }
  }
  return 0;
}