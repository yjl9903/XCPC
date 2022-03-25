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

int n, a[maxn];
vector<PII> evs;

bool check(int x) {
  int l = -inf, r = inf;
  for (int i = 1; i <= n; i++) {
    if (abs(a[i]) <= x) continue;
    l = max(l, a[i] - x);
    r = min(r, a[i] + x);
  }
  return l <= r;
}

int main() {
  int T = gi();
  while (T--) {
    n = gi();
    int l = 0, r = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
      a[i] = gi();
      r = max(r, abs(a[i]));
    }
    while (l <= r) {
      int m = (l + r) / 2;
      if (check(m)) {
        r = m - 1; ans = m;
      } else {
        l = m + 1;
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}