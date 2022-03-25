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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

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
        for (int i = 0; i < n; i++) rk[str[i]] = 1;
        for (int i = 0; i < m; i++) rk[i + 1] += rk[i];
        for (int i = 0; i < n; i++) s[i] = rk[str[i]] - 1;
        return rk[m];
    }
    template<typename T>
    void build(int nn, const T* str) {
        n = nn;
        int m = mapCharToInt(++n, str);
        sais(n, m, s, t, p);
        for (int i = 0; i < n; i++) rk[sa[i]] = i;
        for (int i = 0, k = 0; i < n; i++) {
            if (k) k--;
            int j = sa[rk[i] - 1];
            while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
            h[rk[i]] = k;
        }
    }
}

int n, k;
char s[maxn];

int main() {
  scanf("%d%d%s", &n, &k, s + 1);
  for (int i = 1; i <= k; i++) s[n + i] = s[i];
  SA::build(n + k, s);
  int mn = n + n, pos = -1;
  for (int i = 1; i <= k; i++) {
    int mx = SA::rk[i], p = i;
    for (int j = i; j <= n; j += k) {
      if (SA::rk[j] > mx) {
        mx = SA::rk[j]; p = j;
      }
    }
    if (mx < mn) {
      mn = mx; pos = p;
    }
  }
  for (int i = 0; i < k; i++) {
    putchar(s[pos + i]);
  }
  puts("");
  return 0;
}