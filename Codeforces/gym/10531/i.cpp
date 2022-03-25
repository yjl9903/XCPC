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
const int maxn = 200000 + 5;

struct fastIO {
  static const int SIZE = 1 << 20;
  char s[SIZE]; int it, len;
  fastIO() { it = len = 0; }
  inline char get() {
    if (it < len) return s[it++];
    it = 0; len = fread(s, 1, SIZE, stdin);
    if (len == 0) return EOF;
    else return s[it++];
  }
  inline bool notend() {
    char c = get();
    while (c == ' ' || c == '\n') c = get();
    if (it > 0) it--;
    return c != EOF;
  }
} buff;
inline int gi() {
  int r = 0; bool ng = 0;
  char c = buff.get();
  while (c != '-' && (c < '0' || c > '9')) c = buff.get();
  if (c == '-') ng = 1, c = buff.get();
  while (c >= '0' && c <= '9') r = r * 10 + c - '0', c = buff.get();
  return ng ? -r : r;
}

int n, S, b[maxn];
bool vis[maxn];
PII a[maxn];
ll suf[maxn];

int main() {
  n = gi();
  S = gi();
  for (int i = 1; i <= n; i++) {
    a[i].first = gi();
  }
  for (int i = 1; i <= n; i++) {
    a[i].second = gi();
  }
  sort(a + 1, a + 1 + n, [&](PII a, PII b) {
    if (a.second == a.second) {
      return a.first < b.first;
    }
    return a.second > b.second;
  });
  for (int i = 0; i < n; i++) {
    int p = 0;
    ll mn = S + 1;
    int ch = -1, cp = -1;
    for (int j = 1; j <= n; j++) {
      if (vis[j]) continue;
      while (p < i && a[j].second < b[p]) p++;
      ll cur = 1ll * p * a[j].second + a[j].first + suf[p];
      if (cur < mn) {
        mn = cur;
        ch = j;
        cp = p;
      }
    }
    dbg(i, ch, cp, mn);
    if (S >= mn) {
      S -= mn;
      for (int j = i; j > cp; j--) {
        b[j] = b[j - 1];
      }
      b[cp] = a[ch].second;
      suf[i + 1] = 0;
      for (int j = i; j >= 0; j--) {
        suf[j] = b[j] + suf[j + 1];
      }
      vis[ch] = true;
      // for (int j = 0; j <= i; j++) dbg(b[j]);
      // for (int x: vec) dbg(x);
    } else {
      printf("%d\n", i);
      return 0;
    }
  }
  printf("%d\n", n);
  return 0;
}