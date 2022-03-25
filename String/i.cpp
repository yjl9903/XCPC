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
const int maxn = 100000 + 5;

namespace Runs {
  struct SA {
    int n, m, sa[maxn], h[maxn], c[maxn], x[maxn], y[maxn];
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
    int dp[21][maxn];
    void build(int nn, const char* s) {
      n = nn; m = 255;
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
      for (int j = 1; j < 21; j++) {
        for (int i = 1; i + (1 << j) <= n + 1; i++) {
          dp[j][i] = min(dp[j - 1][i], dp[j - 1][i + (1 << (j - 1))]);
        }
      }
    }
    int qlcp(int l, int r) {
      if (l < 1 || l > n) return 0;
      if (r < 1 || r > n) return 0;
      if (l == r) return n - l + 1;
      l = x[l]; r = x[r];
      if (l > r) swap(l, r);
      l++; int k = __lg(r - l + 1);
      return min(dp[k][l], dp[k][r - (1 << k) + 1]);
    }
  } ori, rev;

  int n; char s[maxn];

  bool cmp(int x, int y) {
    int len = ori.qlcp(x, y);
    if (x + len > n) return false;
    if (y + len > n) return true;
    return s[x + len] < s[y + len];
  }

  vector<PII> ps;
  set<PII> mp;
  void add(int l, int r, int p) {
    if (mp.count({l, r})) return ;
    // Run => (l, r, p)
    mp.insert({l, r});
    for (int i = 0; i < p * 2 && l + 2 * p - 1 + i <= r; i++) {
      for (int j = l + 2 * p - 1 + i; j <= r; j += 2 * p) {
        // Primitive Square: [j-2p+1,j]
        ps.emplace_back(j - 2 * p + 1, j);
      }
    }
  }
  void check(int l, int r) {
    int len = r - l;
    int lcp = ori.qlcp(l, r); // lcp of s[l...n], s[r...n]
    int lcs = rev.qlcp(n - l + 2, n - r + 2); // lcs of s[1...l-1], s[1...r-1]
    if (lcp + lcs >= len) {
      add(l - lcs, r + lcp - 1, len);
    }
  }
  void find(int type) {
    static int st[maxn], stn;
    stn = 0; st[stn++] = n + 1;
    for (int i = n; i >= 1; i--) {
      while (stn > 1 && cmp(i, st[stn - 1]) == type) stn--;
      check(i, st[stn - 1]);
      st[stn++] = i;
    }
  }
  vector<PII> build(int nn, char* ss) {
    n = nn;
    for (int i = 1; i <= n; i++) s[i] = ss[i];
    s[n + 1] = 0;
    ori.build(n, ss); // 原串
    reverse(ss + 1, ss + n + 1);
    rev.build(n, ss); // 反串
    mp.clear(); ps.clear();
    find(0); find(1);
    return ps;
  }
}

int n, a[maxn], ri[maxn], le[maxn];
char s[maxn];

void update(int i, int x) {
  for (; i <= n; i += i & -i) a[i] += x;
}
int query(int i) {
  int r = 0;
  for (; i; i -= i & -i) r += a[i];
  return r;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 0; i <= n; i++) {
      a[i] = 0; ri[i] = n + 1; le[i] = 0;
    }
    vector<PII> ps = Runs::build(n, s);
    for (auto& x: ps) {
      ri[x.first] = min(ri[x.first], x.second);
      le[x.second] = max(le[x.second], x.first);
    }
    vector<PII> lf;
    for (int i = 1; i <= n; i++) {
      if (le[i]) {
        lf.push_back({ le[i], i });
        update(i, 1);
      }
    }
    sort(begin(lf), end(lf));
    ll ans = 0; int p = 0;
    for (int i = 1; i <= n; i++) {
      int mn = ri[i] - 1;
      ans += mn - i + 1 - query(mn);
      while (p < (int)lf.size() && lf[p].first == i) {
        update(lf[p].second, -1); p++;
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}