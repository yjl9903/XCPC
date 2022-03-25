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
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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

int n, m, fail[maxn], ri[maxn];
ll ans;
char a[maxn], b[maxn], s[maxn];

struct Query {
  int x, y, tp;
  Query() {}
  Query(int x, int y, int tp): x(x), y(y), tp(tp) {}
  bool operator <(const Query& b) const {
    if (x == b.x) return abs(tp) < abs(b.tp);
    return x < b.x;
  }
};

struct BIT {
  ll a[maxn + 1];
  void update(int i, int x) {
    for (; i <= maxn; i += i & -i) a[i] += x;
  }
  ll query(int i) {
    if (i <= 0) return 0;
    ll r = 0;
    for (; i; i -= i & -i) r += a[i];
    return r;
  }
  ll query(int l, int r) {
    return query(r) - query(l - 1);
  }
} f, g;

namespace exkmp {
  int nxt[maxn], extend[maxn];
  void getnxt(int n, char *s) {
    int p = 1, k = 2; nxt[1] = n;
    while (p + 1 <= n && s[p] == s[p + 1]) p++;
    nxt[2] = p - 1;
    for (int i = 3; i <= n; i++) {
      int len = nxt[i - k + 1];
      if (len + i <= p) nxt[i] = len;
      else {
        int j = max(p - i + 1, 0);
        while (i + j <= n && s[j + 1] == s[i + j]) j++;
        nxt[i] = j; k = i;
        p = i + j - 1;
      }
    }
  }
  void build(int tlen, char *t, int slen, char *s) {
    getnxt(slen, s);
    int p = 1, k = 1;
    while (p <= tlen && p <= slen && t[p] == s[p]) p++;
    p--; extend[1] = p;
    for (int i = 2; i <= tlen; i++) {
      int len = nxt[i - k + 1];
      if (len + i <= p) extend[i] = len;
      else {
        int j = max(p - i + 1, 0);
        while (i + j <= tlen && j <= slen && s[j + 1] == t[i + j]) j++;
        extend[i] = j; k = i;
        p = i + j - 1;
      }
    }
  }
}

int main() {
  scanf("%d%d%s%s%s", &n, &m, a + 1, b + 1, s + 1);
  for (int i = 2; i <= m; i++) {
    int cur = fail[i - 1];
    while (cur && s[cur + 1] != s[i]) cur = fail[cur];
    if (s[cur + 1] == s[i]) cur++;
    fail[i] = cur;
  }
  vector<Query> que;
  for (int i = n, cur = 0; i >= 1; i--) {
    while (cur && s[cur + 1] != a[i]) cur = fail[cur];
    if (s[cur + 1] == a[i]) cur++;
    dbg(i, cur);
    que.emplace_back(i - 1, cur, -1);
    que.emplace_back(min(m, i + m - 2), cur, 1);
  }
  reverse(s + 1, s + 1 + m);
  for (int i = 2; i <= m; i++) {
    int cur = fail[i - 1];
    while (cur && s[cur + 1] != s[i]) cur = fail[cur];
    if (s[cur + 1] == s[i]) cur++;
    fail[i] = cur;
  }
  for (int i = 1, cur = 0; i <= n; i++) {
    while (cur && s[cur + 1] != b[i]) cur = fail[cur];
    if (s[cur + 1] == b[i]) cur++;
    dbg(i, cur);
    que.emplace_back(i, cur, 0);
  }
  sort(begin(que), end(que));
  for (auto& q: que) {
    if (!q.y) continue;
    dbg(q.x, q.y, q.tp);
    if (q.tp == 0) {
      f.update(q.y, q.y);
      g.update(q.y, 1);
    } else {
      ll r = f.query(m - q.y, maxn) + 1ll * (q.y - m + 1) * g.query(m - q.y, maxn);
      ans += q.tp * r;
    }
  }
  printf("%I64d\n", ans);
  return 0;
}