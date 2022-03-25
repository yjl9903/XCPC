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
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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
const int maxn = 500 + 5;
const int maxq = 3e5 + 5;

int n, m, q;
int sum[maxn][maxn], row[maxn][maxn][4], col[maxn][maxn][4];
char mp[maxn][maxn];

int id(char c) {
  if (c == 'R') return 0;
  if (c == 'G') return 1;
  if (c == 'Y') return 2;
  if (c == 'B') return 3;
  assert(false);
}

struct Rect {
  int x, y, l;
  bool operator<(const Rect & b)  const {
    return l < b.l;
  }
};

int r1[maxq], c1[maxq], r2[maxq], c2[maxq], ans[maxq];

int main() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%s", mp[i] + 1);
  }
  for (int i = 1; i <= q; i++) {
    scanf("%d%d%d%d", r1 + i, c1 + i, r2 + i, c2 + i);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      for (int k = 0; k < 4; k++) {
        row[i][j][k] = row[i][j - 1][k];
      }
      row[i][j][id(mp[i][j])]++;
    }
  }
  for (int j = 1; j <= m; j++) {
    for (int i = 1; i <= n; i++) {
      for (int k = 0; k < 4; k++) {
        col[i][j][k] = col[i - 1][j][k];
      }
      col[i][j][id(mp[i][j])]++;
    }
  }
  auto chkR = [&](int i, int l, int r, char c) {
    return row[i][r][id(c)] - row[i][l - 1][id(c)] == r - l + 1;
  };
  auto chkC = [&](int j, int u, int d, char c) {
    return col[d][j][id(c)] - col[u - 1][j][id(c)] == d - u + 1;
  };
  vector<Rect> rect;
  for (int i = 1; i + 1 <= n; i++) {
    for (int j = 1; j + 1 <= m; j++) {
      if (mp[i][j] != 'R') continue;
      int mx = 1;
      for (int l = 2; i + l + l - 1 <= n && j + l + l - 1 <= m; l++) {
        if (chkR(i + l - 1, j, j + l - 1, 'R') && chkC(j + l - 1, i, i + l - 1, 'R')) {
          mx = l;
        } else {
          break;
        }
      }
      bool flag = true;
      for (int k = 1; k <= mx && flag; k++) {
        flag &= chkR(i + k - 1, j + mx, j + mx + mx - 1, 'G');
      }
      for (int k = 1; k <= mx && flag; k++) {
        flag &= chkR(i + mx + k - 1, j, j + mx - 1, 'Y');
      }
      for (int k = 1; k <= mx && flag; k++) {
        flag &= chkR(i + mx + k - 1, j + mx, j + mx + mx - 1, 'B');
      }
      if (flag) {
        rect.push_back((Rect){ i, j, mx });
      }
    }
  }
  sort(begin(rect), end(rect));
  for (auto& x: rect) {
    dbg(x.x, x.y, x.l);
  }
  int p = 0;
  for (int l = 1; l + l <= min(n, m) && p < (int)rect.size(); l++) {
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= m; j++) {
        sum[i][j] = 0;
      }
    }
    while (p < (int)rect.size() && rect[p].l == l) {
      sum[rect[p].x][rect[p].y] = 1; p++;
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        sum[i][j] -= sum[i - 1][j - 1];
        sum[i][j] += sum[i - 1][j];
        sum[i][j] += sum[i][j - 1];
      }
    }
    auto query = [&](int r1, int c1, int r2, int c2) -> int {
      int ans = sum[r2][c2] + sum[r1 - 1][c1 - 1] - sum[r2][c1 - 1] - sum[r1 - 1][c2];
      return ans;
    };
    for (int i = 1; i <= q; i++) {
      if (l + l > min(r2[i] - r1[i] + 1, c2[i] - c1[i] + 1)) continue;
      if (query(r1[i], c1[i], r2[i] - l - l + 1, c2[i] - l - l + 1)) {
        ans[i] = l;
      }
    }
  }
  for (int i = 1; i <= q; i++) {
    printf("%d\n", 4 * ans[i] * ans[i]);
  }
  return 0;
}