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
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, a[maxn], dp[20][maxn];

int qmin(int l, int r) {
  int k = __lg(r - l + 1);
  int x = dp[k][l], y = dp[k][r - (1 << k) + 1];
  if (a[x] <= a[y]) return x;
  else return y;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      dp[0][i] = i;
    }
    map<int, PII> pre, suf;
    for (int i = 1, j = 1, mx = 0; i <= n; i = j) {
      mx = a[i];
      while (j <= n && a[j] <= mx) j++;
      pre[mx] = { i, j - 1 };
    }
    for (int i = n, j = n, mx = 0; i >= 1; i = j) {
      mx = a[i];
      while (j >= 1 && a[j] <= mx) j--;
      suf[mx] = { j + 1, i };
    }
    for (int j = 1; j < 20; j++) {
      for (int i = 1; i + (1 << j) <= n + 1; i++) {
        int l = dp[j - 1][i];
        int r = dp[j - 1][i + (1 << (j - 1))];
        if (a[l] <= a[r]) dp[j][i] = l;
        else dp[j][i] = r;
      }
    }
    int ansx = -1, ansy = -1;
    auto getPos = [&](PII x, int l, int r) -> int {
      if (x.second < l) {
        return -1;
      } else if (r < x.first) {
        return -1;
      } else {
        return max(x.first, l);
      }
    };
    function<void(int, int)> solve = [&](int l, int r) {
      if (ansx != -1) return ;
      if (l > r) return ;
      int pos = qmin(l, r);
      int x = pre.count(a[pos]) ? getPos(pre[a[pos]], l - 1, pos - 1) : -1;
      int y = suf.count(a[pos]) ? getPos(suf[a[pos]], pos + 1, r + 1) : -1;
      if (x != -1 && y != -1) {
        ansx = x;
        ansy = n - y + 1;
        return ;
      }
      solve(l, pos - 1);
      solve(pos + 1, r);
    };
    solve(1, n);
    if (ansx == -1 && ansy == -1) {
      puts("NO");
    } else {
      puts("YES");
      printf("%d %d %d\n", ansx, n - ansx - ansy, ansy);
    }
  }
  return 0;
}