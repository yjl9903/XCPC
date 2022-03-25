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
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, m, q, a[maxn], fail[maxn];

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

int tot, root[maxn], ls[maxn * 20], rs[maxn * 20], sum[maxn * 20];
void update(int i, int pre, int l, int r, int& rt) {
  rt = ++tot;
  ls[rt] = ls[pre];
  rs[rt] = rs[pre];
  sum[rt] = sum[pre] + 1;
  if (l == r) return ;
  int m = (l + r) / 2;
  if (i <= m) update(i, ls[pre], lson);
  else update(i, rs[pre], rson);
}
int query(int L, int R, int l, int r, int rt) {
  if (!rt) return 0;
  if (L <= l && r <= R) return sum[rt];
  int m = (l + r) / 2, ans = 0;
  if (L <= m) ans += query(L, R, lson);
  if (R > m) ans += query(L, R, rson);
  return ans;
}

int sa[maxn], rk[maxn], cnt[maxn];
int front(int c, int pos) {
  int l = 1, r = n, ans = 0;
  auto check = [&](int i) {
    // s_{i}s_{i+1} <= cs1s2...
    if (i == n) {
      return a[i] <= c;
    }
    if (a[i] != c) {
      return a[i] < c;
    }
    return rk[i + 1] <= rk[1];
  };
  while (l <= r) {
    int m = (l + r) / 2;
    if (check(sa[m])) {
      ans = m; l = m + 1;
    } else {
      r = m - 1;
    }
  }
  if (pos == 1) {
    return ans + 1;
  } else {
    if (rk[pos - 1] <= ans) {
      return rk[pos - 1];
    } else {
      return rk[pos - 1] + 1;
    }
  }
}

int get(int c, int pos) {
  int l = rk[pos] + 1, r = n, ans = rk[pos];
  auto check = [&](int i) {
    // s_{i}s_{i+1}... <= s_{pos}...c
    if (SA::qlcp(i, pos) == n - pos + 1) {
      return a[i + n - pos + 1] < c;
    } else {
      return false;
    }
  };
  while (l <= r) {
    int m = (l + r) / 2;
    if (check(sa[m])) {
      ans = m; l = m + 1;
    } else {
      r = m - 1;
    }
  }
  return ans - rk[pos];
}
int back(int c, int pos) {
  if (pos == n + 1) {
    return cnt[c - 1] + 1;
  }
  int ans = rk[pos];
  if (c <= a[pos]) {
    ans++;
  }
  if (c >= 1) {
    int x = query(1, c - 1, 1, m, root[pos]);
    ans -= query(1, c - 1, 1, m, root[pos]);
  }
  ans += get(c, pos);
  return ans;
}

int main() {
  int T; scanf("%d", &T);
  int qcnt = 0;
  while (T--) {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i <= m; i++) {
      cnt[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      cnt[a[i]]++;
    }
    for (int i = 1; i <= m; i++) {
      cnt[i] += cnt[i - 1];
    }

    SA::build(n, a + 1);
    for (int i = 1; i <= n; i++) {
      sa[i] = SA::sa[i] + 1;
      rk[i] = SA::rk[i - 1];
    }

    reverse(a + 1, a + 1 + n);
    tot = fail[1] = root[n + 1] = 0;
    for (int i = 2; i <= n; i++) {
      int cur = fail[i - 1];
      while (cur && a[cur + 1] != a[i]) cur = fail[cur];
      if (a[cur + 1] == a[i]) cur++;
      fail[i] = cur;
    }
    reverse(a + 1, a + 1 + n);
    reverse(fail + 1, fail + 1 + n);
    for (int i = n; i >= 1; i--) {
      int len = fail[i];
      fail[i] = n + 1 - len;
      if (len) {
        update(a[i + len], root[fail[i]], 1, m, root[i]);
      } else {
        root[i] = 0;
      }
    }
    
    int ans = 0, op, c, i;
    while (q--) {
      scanf("%d%d%d", &op, &c, &i);
      c ^= ans;
      i ^= ans;
      if (op == 1) {
        ans = front(c, i);
      } else if (op == 2) {
        ans = back(c, i);
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}