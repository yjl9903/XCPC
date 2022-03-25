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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 2000000 + 5;
const int maxk = 3000 + 5;

namespace SA {
  int n, sa[maxn], rk[maxn], h[maxn];
  int s[maxn << 1], t[maxn << 1], p[maxn], cnt[maxn], cur[maxn];
  void sais(int n, int m, int* s, int* t, int* p) {
    int n1 = t[n - 1] = 0, ch = rk[0] = -1, *s1 = s + n;
    auto pushS = [&](int x) {
      sa[cur[s[x]]--] = x;
    };
    auto pushL = [&](int x) {
      sa[cur[s[x]]++] = x;
    };
    auto isort = [&](const int* v) {
      fill_n(sa, n, -1); fill_n(cnt, m, 0);
      for (int i = 0; i < n; i++) cnt[s[i]]++;
      for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
      for (int i = 0; i < m; i++) cur[i] = cnt[i] - 1;
      for (int i = n1 - 1; ~i; i--) pushS(v[i]);
      for (int i = 1; i < m; i++) cur[i] = cnt[i - 1];
      for (int i = 0; i < n; i++) if (sa[i] > 0 && t[sa[i] - 1]) pushL(sa[i] - 1);
      for (int i = 0; i < m; i++) cur[i] = cnt[i] - 1;
      for (int i = n - 1; ~i; i--) if (sa[i] > 0 && !t[sa[i] - 1]) pushS(sa[i] - 1);
    };
    for (int i = n - 2; ~i; i--) t[i] = s[i] == s[i + 1] ? t[i + 1] : s[i] > s[i + 1];
    for (int i = 1; i < n; i++) rk[i] = t[i - 1] && !t[i] ? (p[n1] = i, n1++) : -1;
    isort(p);
    for (int i = 0, x, y; i < n; i++) if (~(x = rk[sa[i]])) {
      if (ch < 1 || p[x + 1] - p[x] != p[y + 1] - p[y]) ch++;
      else for (int j = p[x], k = p[y]; j <= p[x + 1]; j++, k++)
      if ((s[j] << 1 | t[j]) != (s[k] << 1 | t[k])) { ch++; break;}
      s1[y = x] = ch;
    }
    if (ch + 1 < n1) sais(n1, ch + 1, s1, t + n, p + n1);
    else for (int i = 0; i < n1; i++) sa[s1[i]] = i;
    for (int i = 0; i < n1; i++) s1[i] = p[sa[i]];
    isort(s1);
  }
  template<typename T>
  int mapCharToInt(int n, const T* str) {
    int m = *max_element(str, str + n);
    fill_n(rk, m + 1, 0);
    rk[0] = 1;
    for (int i = 0; i < n; i++) rk[str[i]] = 1;
    for (int i = 0; i < m; i++) rk[i + 1] += rk[i];
    for (int i = 0; i < n; i++) s[i] = rk[str[i]] - 1;
    s[n] = 0;
    return rk[m];
  }
  int dp[21][maxn];
  template<typename T>
  void build(int nn, const T* str) {
    n = nn;
    int m = mapCharToInt(n++, str);
    assert(s[n - 1] == 0);
    sais(n, m, s, t, p);
    for (int i = 0; i < n; i++) rk[sa[i]] = i;
    for (int i = 0, k = 0; i < n; i++) {
      if (k) k--;
      int j = sa[rk[i] - 1];
      while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
      h[rk[i]] = k;
    }
    for (int i = 1; i <= n; i++) dp[0][i] = h[i];
    for (int j = 1; j < 21; j++) {
      for (int i = 1; i + (1 << j) <= n + 1; i++) {
        dp[j][i] = min(dp[j - 1][i], dp[j - 1][i + (1 << (j - 1))]);
      }
    }
  }
  int qlcp(int l, int r) {
    l--; r--;
    if (l < 0) return 0;
    if (r < 0) return 0;
    if (l == r) return n - 1 - l;
    l = rk[l]; r = rk[r];
    if (l > r) swap(l, r);
    l++;
    int k = __lg(r - l + 1);
    return min(dp[k][l], dp[k][r - (1 << k) + 1]);
  }
}

struct Ope {
  int tp, pos;
  char ch;
};

int n, m, k;
int f[maxk][maxk];
char buf[maxn];

int lcp(int x, int y) {
  return SA::qlcp(x, n + 1 + y);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &m, &k);
    scanf("%s%s", buf + 1, buf + 2 + n);
    buf[n + 1] = '$';
    SA::build(n + 1 + m, buf + 1);
    for (int i = 0; i <= k; i++) {
      for (int j = -k; j <= k; j++) {
        f[i][j + k] = -1;
      }
    }
    f[0][k] = lcp(1, 1);
    for (int i = 1; i <= k; i++) {
      for (int j = -i + 1; j <= i - 1; j++) {
        int x = f[i - 1][j + k] + 1;
        if (x == 0) continue;
        int y = x + j;
        if (x <= n && y <= m) {
          // s[x] -> t[y]
          f[i][j + k] = max(f[i][j + k], x + 1 + lcp(x + 1, y + 1) - 1);
        }
        if (y <= m) {
          // ins before s[x]
          f[i][j + k + 1] = max(f[i][j + k + 1], x + lcp(x, y + 1) - 1);
        }
        if (x <= n) {
          // del s[x]
          f[i][j + k - 1] = max(f[i][j + k - 1], x + 1 + lcp(x + 1, y) - 1);
        }
      }
    }
    int ans = -1;
    for (int i = 0; i <= k; i++) {
      if (f[i][m - n + k] == n) {
        ans = i;
        break;
      }
    }
    if (ans == -1) {
      puts("NO");
    } else {
      puts("YES");
      vector<Ope> plan;
      int last = n, d = m - n;
      for (int i = ans - 1; i >= 0; i--) {
        {
          int x = f[i][d + k] + 1;
          int y = x + d;
          if (x != 0) {
            if (x <= n && 1 <= y && y <= m) {
              if (x + 1 + lcp(x + 1, y + 1) - 1 == last) {
                // replace
                last = f[i][d + k];
                plan.push_back({ 3, y, buf[n + 1 + y] });
                continue;
              }
            }
          }
        }
        {
          int x = f[i][d - 1 + k] + 1;
          int y = x + d - 1;
          if (x != 0) {
            if (y <= m) {
              if (x + lcp(x, y + 1) - 1 == last) {
                // insert
                last = f[i][d - 1 + k];
                d--;
                plan.push_back({ 1, y, buf[n + 1 + y] });
                continue;
              }
            }
          }
        }
        {
          int x = f[i][d + 1 + k] + 1;
          int y = x + d + 1;
          if (x != 0) {
            if (x <= n) {
              if (x + 1 + lcp(x + 1, y) - 1 == last) {
                // del
                last = f[i][d + 1 + k];
                d++;
                plan.push_back({ 2, y });
                continue;
              }
            }
          }
        }
        assert(false);
      }
      reverse(plan.begin(), plan.end());
      printf("%d\n", plan.size());
      for (auto x: plan) {
        if (x.tp == 1) {
          printf("INSERT %d %c\n", x.pos, x.ch);
        } else if (x.tp == 2) {
          printf("DELETE %d\n", x.pos);
        } else if (x.tp == 3) {
          printf("REPLACE %d %c\n", x.pos, x.ch);
        }
      }
    }
  }
  return 0;
}