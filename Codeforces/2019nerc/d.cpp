#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <set>
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
const int maxn = 500 + 5;
const int maxc = 200 + 5;

struct Node {
  int l, r, c;
  bool operator<(const Node& b) const {
    return r < b.r;
  }
} a[maxn];

int n, p[maxn], minp[maxn], vis[maxn], dp[maxn];
set<int> col[maxn];

struct DS {
  int a[maxn];
  void clear() {
    for (int i = 0; i <= n; i++) a[i] = 0;
  }
  void update(int i, int x) {
    for (; i <= n; i++) a[i] += x;
  }
  int query(int l, int r) {
    return a[r] - a[l - 1];
  }
} h[maxc];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 0; i <= 200; i++) h[i].clear();
    for (int i = 1; i <= n; i++) {
      scanf("%d%d%d", &a[i].l, &a[i].r, &a[i].c);
      col[i].clear();
    }
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; i++) {
      p[i] = -1;
      for (int j = 1; j <= i; j++) {
        if (a[j].r >= a[i].l) {
          if (p[i] == -1) p[i] = j;
          col[i].insert(a[j].c);
          col[j].insert(a[i].c);
        }
      }
    }
    minp[n + 1] = inf;
    for (int i = n; i >= 1; i--) minp[i] = min(minp[i + 1], p[i]);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      vis[i] = 0;
      if (col[i].count(0)) {
        if ((int)col[i].size() >= 3) vis[i] = -1;
        else if ((int)col[i].size() == 2) vis[i] = *col[i].rbegin();
      } else {
        vis[i] = -1;
        if ((int)col[i].size() == 1) ans++;
      }
    }
    for (int i = 1; i <= n; i++) {
      dp[i] = dp[i - 1];
      if (vis[i] == -1) continue;
      int le = min(p[i], minp[p[i]]);
      h[vis[i]].update(le, 1);
      int l = 1, r = 200;
      if (vis[i]) l = vis[i], r = vis[i];
      for (int c = l; c <= r; c++) {
        for (int j = 0; j < le; j++) {
          int tot = h[c].query(j + 1, n) + h[0].query(j + 1, n);
          dp[i] = max(dp[i], dp[j] + tot);
        }
      }
    }
    printf("%d\n", ans + dp[n]);
  }
  return 0;
}