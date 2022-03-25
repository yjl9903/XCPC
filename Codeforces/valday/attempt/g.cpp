#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
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
const int maxn = 500000 + 5;
const int S = 2200;

struct fastIO {
  char s[100000]; int it,len;
  fastIO() { it = len = 0; }
  inline char get() {
    if (it < len) return s[it++];
    it = 0; len = fread(s, 1, 100000, stdin);
    if (len == 0) return EOF;
    else return s[it++];
  }
  bool notend() {
    char c = get();
    while(c == ' ' || c == '\n') c = get();
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

int n, q, a[maxn], b[maxn];
int bel[maxn], L[maxn], R[maxn];

struct Block {
  int n; 
  ll sumb, a[S + 1], b[S + 1], suf[S + 1];
  vector<pair<ll,int> > v;
  void build() {
    for (int i = 0; i < n; i++) {
      sumb += b[i];
      v.emplace_back(a[i] - b[i], i);
    }
    sort(begin(v), end(v));
    for (int i = n - 1; i >= 0; i--) {
      suf[i] = suf[i + 1];
      suf[i] += a[v[i].second] - b[v[i].second];
    }
  }
  ll query(ll& pa, ll& pb) {
    int pos = lower_bound(begin(v), end(v), make_pair(pb - pa, -1)) - begin(v);
    ll ans = suf[pos] + sumb + pb * n + (n - pos) * (pa - pb);
    pa += a[n - 1]; pb += b[n - 1];
    return ans;
  }
} blk[maxn / S + 5];

ll bruteforce(int l, int r, ll& pa, ll& pb) {
  ll ans = 0;
  for (int i = l; i <= r; i++) {
    pa += a[i]; pb += b[i];
    ans += max(pa, pb);
  }
  return ans;
}

int main() {
  n = gi(); q = gi();
  for (int i = 1; i <= n; i++) a[i] = gi();
  for (int i = 1; i <= n; i++) b[i] = gi();
  for (int i = 1, tot = 1; i <= n; i += S, tot++) {
    L[tot] = i; R[tot] = min(n, i + S - 1);
    blk[tot].n = R[tot] - L[tot] + 1;
    ll sa = 0, sb = 0;
    for (int j = L[tot]; j <= R[tot]; j++) {
      bel[j] = tot;
      sa += a[j]; sb += b[j];
      blk[tot].a[j - L[tot]] = sa;
      blk[tot].b[j - L[tot]] = sb;
    }
    blk[tot].build();
  }
  while (q--) {
    int l = gi();
    int r = gi();
    ll ans = 0, pa = 0, pb = 0;
    if (bel[l] == bel[r]) {
      ans = bruteforce(l, r, pa, pb);
    } else {
      ans = bruteforce(l, R[bel[l]], pa, pb);
      for (int i = bel[l] + 1; i < bel[r]; i++) {
        ans += blk[i].query(pa, pb);
      }
      ans += bruteforce(L[bel[r]], r, pa, pb);
    }
    printf("%I64d\n", ans);
  }
  return 0;
}