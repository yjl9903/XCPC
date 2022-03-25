#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;
const int maxn = 100000 + 5;

namespace SA {
  const int L = 18;

  int n, m, sa[maxn], h[maxn], c[maxn], x[maxn], y[maxn];
  int dp[L][maxn];
  
  void rsort() {
    for (int i = 1; i <= m; i++) c[i] = 0;
    for (int i = 1; i <= n; i++) c[x[i]]++;
    for (int i = 1; i <= m; i++) c[i] += c[i - 1];
    for (int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];
  }
  int cmp(int i, int j, int k) {
    int a = i + k > n ? -1 : y[i + k];
    int b = j + k > n ? -1 : y[j + k];
    return y[i] == y[j] && a == b;
  }
  void build(int nn, int* s) {
    n = nn; m = nn + 1;
    for (int i = 1; i <= n; i++) x[i] = s[i], y[i] = i;
    rsort();
    for (int k = 1, p; k <= n; k += k, m = p) {
      p = 0;
      for (int i = n; i > n - k; i--) y[++p] = i;
      for (int i = 1; i <= n; i++) if (sa[i] > k) y[++p] = sa[i] - k;
      rsort();
      for (int i = 1; i <= n; i++) swap(x[i], y[i]);
      x[sa[1]] = p = 1;
      for (int i = 2; i <= n; i++) x[sa[i]] = cmp(sa[i], sa[i - 1], k) ? p : ++p;
    }
    for (int i = 1; i <= n; i++) x[sa[i]] = i;
    for (int i = 1, k = 0; i <= n; i++) {
      if (k) k--;
      int j = sa[x[i] - 1];
      while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
      h[x[i]] = k;
    }
    for (int i = 1; i <= n; i++) dp[0][i] = h[i];
    for (int j = 1; j < L; j++) {
      for (int i = 1; i + (1 << j) <= n + 1; i++) {
        dp[j][i] = min(dp[j - 1][i], dp[j - 1][i + (1 << (j - 1))]);
      }
    }
  }
  int qlcp(int l, int r) {
    if (l <= 0 || l > n) return 0;
    if (r <= 0 || r > n) return 0;
    if (l == r) return n - l + 1;
    l = x[l]; r = x[r];
    if (l > r) swap(l, r);
    l++; int k = __lg(r - l + 1);
    return min(dp[k][l], dp[k][r - (1 << k) + 1]);
  }
}

int n, a[maxn], ord[maxn];
int ch[maxn][26], nxt[maxn][26];
char s[maxn];

int lcp(int x, int y) {
  int Bx = x, By = y;
  int len = 0;
  x--; y--;
  for (int j = 0; j < 26 && x + 1 <= n && y + 1 <= n; j++) {
    int l = SA::qlcp(x + 1, y + 1);
    if (x + 1 + l < nxt[Bx][j] && y + 1 + l < nxt[By][j]) {
      return len + l;
    }
    if (nxt[Bx][j] - Bx == nxt[By][j] - By) {
      len += nxt[Bx][j] - x;
      x = nxt[Bx][j];
      y = nxt[By][j];
    } else if (nxt[Bx][j] - Bx < nxt[By][j] - By) {
      return len + nxt[Bx][j] - x - 1;
    } else {
      return len + nxt[By][j] - y - 1;
    }
  }
  return len + SA::qlcp(x + 1, y + 1);
}

int main() {
  scanf("%d%s", &n, s + 1);
  vector<int> last(26, -1);
  for (int i = 1; i <= n; i++) {
    ord[i] = i;
    int ch = s[i] - 'a';
    if (last[ch] == -1) {
      a[i] = n + 1;
    } else {
      a[i] = i - last[ch];
    }
    last[ch] = i;
  }
  SA::build(n, a);
  for (int j = 0; j < 26; j++) {
    nxt[n + 1][j] = n + n + n;
    ch[n + 1][j] = n + n + n;
  }
  for (int i = n; i >= 1; i--) {
    memcpy(nxt[i], nxt[i + 1], sizeof nxt[i + 1]);
    nxt[i][s[i] - 'a'] = i;
  }
  for (int i = n; i >= 1; i--) {
    memcpy(ch[i], nxt[i], sizeof nxt[i]);
    sort(nxt[i], nxt[i] + 26);
  }
  sort(ord + 1, ord + 1 + n, [&](int x, int y) {
    int len = lcp(x, y);
    if (x + len > n || y + len > n) {
      return x + len > n;
    }
    int chX = a[x + len], chY = a[y + len];
    for (int j = 0; j < 26; j++) {
      if (ch[x][j] == x + len) {
        chX = 0;
        break;
      }
    }
    for (int j = 0; j < 26; j++) {
      if (ch[y][j] == y + len) {
        chY = 0;
        break;
      }
    }
    return chX < chY;
  });
  ll ans = 1ll * n * (n + 1) / 2;
  for (int i = 1; i < n; i++) {
    ans -= lcp(ord[i], ord[i + 1]);
  }
  printf("%lld\n", ans);
  return 0;
}