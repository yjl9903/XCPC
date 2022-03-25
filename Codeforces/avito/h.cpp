#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <map>
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
typedef unsigned long long ull;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;
const int seed = 135;
const int p1 = 1e9 + 7, p2 = 1e9 + 9;

ull xp1[maxn], xp2[maxn], xp[maxn];
struct Hash {
  static void init() {
    xp1[0] = xp2[0] = xp[0] = 1;
    for (int i = 1; i < maxn; ++i) {
      xp1[i] = xp1[i - 1] * seed % p1;
      xp2[i] = xp2[i - 1] * seed % p2;
      xp[i] = xp[i - 1] * seed;
    }
  }

  ull h[maxn];
  ull build(int n, const char* s) {
    ull r1 = 0, r2 = 0;
    for (int i = 1; i <= n; i++) {
      r1 = (r1 * seed + s[i]) % p1;
      r2 = (r2 * seed + s[i]) % p2;
      h[i] = (r1 << 32) | r2;
    }
    return h[n];
  }

  ull query(int l, int r) {
    int len = r - l + 1;
    unsigned int mask32 = ~(0u);
    ull left1 = h[l - 1] >> 32, right1 = h[r] >> 32;
    ull left2 = h[l - 1] & mask32, right2 = h[r] & mask32;
    return (((right1 - left1 * xp1[len] % p1 + p1) % p1) << 32) |
            (((right2 - left2 * xp2[len] % p2 + p2) % p2));
  }
} hs, ht;

ull offset(ull a, ull b, int len) {
  unsigned int mask32 = ~(0u);
  ull a1 = a >> 32, a2 = a & mask32;
  ull b1 = b >> 32, b2 = b & mask32;
  return (((b1 + a1 * xp1[len] % p1) % p1) << 32) | 
          ((b2 + a2 * xp2[len] % p2) % p2);
}

struct pam {
  int sz, tot, last;
  int ch[maxn][26], len[maxn], fail[maxn];
  int dif[maxn], slink[maxn];
  int cnt[maxn], dep[maxn], pos[maxn], pnode[maxn];
  char s[maxn];
  int node(int l) {
    sz++; ms(ch[sz], 0);
    len[sz] = l; fail[sz] = cnt[sz] = dep[sz] = 0;
    return sz;
  }
  void clear() {
    sz = -1; last = 0;
    s[tot = 0] = '$';
    node(0); node(-1);
    fail[0] = 1;
  }
  int getfail(int x) {
    while (s[tot - len[x] - 1] != s[tot]) x = fail[x];
    return x;
  }
  int insert(char c) {
    s[++tot] = c;
    int now = getfail(last);
    if (!ch[now][c - 'a']) {
      int x = node(len[now] + 2);
      fail[x] = ch[getfail(fail[now])][c - 'a'];
      dep[x] = dep[fail[x]] + 1;
      ch[now][c - 'a'] = x;

      dif[x] = len[x] - len[fail[x]];
      if (dif[x] == dif[fail[x]]) slink[x] = slink[fail[x]];
      else slink[x] = fail[x];
    }
    last = ch[now][c - 'a'];
    cnt[last]++;
    return last;
  }
  void build(int n, const char* s) {
    clear();
    for (int i = 1; i <= n; i++) {
      int u = insert(s[i]);
      pos[u] = i; pnode[i] = u;
    }
  }
  int get(int u, int ql) {
		if (ql > len[u]) return len[u];
		while (true) {
			int l = len[slink[u]];
			int d = dif[u];
			if (ql >= l) {
				return ((ql - l) / d) * d + l;
			}
			u = slink[u];
		}
    return 0;
	}
} ps, pt, psr, ptr;

char s[maxn], t[maxn];
int slen, tlen;

bool checkPad(int l, int r, pam& p) {
  return p.get(p.pnode[r], r - l + 1) == r - l + 1;
}
int checkDec(int l, int r, pam& p, pam& pr) {
  int a = p.get(p.pnode[r], r - l + 1);
  if (l <= r - a && r - a + 1 <= r && checkPad(l, r - a, p)) {
    return r - a - l + 1;
  }
  a = pr.get(pr.pnode[pr.tot - l + 1], r - l + 1);
  if (l <= l + a - 1 && l + a <= r && checkPad(l + a, r, p)) {
    return a;
  }
  return -1;
}

int main() {
  Hash::init();

  scanf("%s%s", s + 1, t + 1);
  slen = strlen(s + 1); tlen = strlen(t + 1);

  ps.build(slen, s);
  hs.build(slen, s);
  pt.build(tlen, t);
  ht.build(tlen, t);
  reverse(s + 1, s + slen + 1);
  reverse(t + 1, t + tlen + 1);
  psr.build(slen, s);
  ptr.build(tlen, t);

  ll ans = 1ll * (ps.sz - 1) * (pt.sz - 1);

  map<ull,int> padmps, padmpt;
  map<ull,int> mps, mpt;

  for (int i = 2; i <= ps.sz; i++) {
    padmps[hs.query(ps.pos[i] - ps.len[i] + 1, ps.pos[i])]++;
    int p = ps.fail[i];
    if (p <= 1) continue;
    if (ps.len[i] <= ps.len[p] * 2) {
      int l = ps.pos[i] - (ps.len[i] - ps.len[p]) + 1;
      int r = ps.pos[i];
      mps[hs.query(l, r)]++;
    }
  }
  
  for (int i = 2; i <= pt.sz; i++) {
    padmpt[ht.query(pt.pos[i] - pt.len[i] + 1, pt.pos[i])]++;
    int p  = pt.fail[i];
    if (p <= 1) continue;
    if (pt.len[i] <= pt.len[p] * 2) {
      int l = pt.pos[i] - pt.len[i] + 1;
      int r = l + (pt.len[i] - pt.len[p]) - 1;
      mpt[ht.query(l, r)]++;
    }
  }

  for (int i = 2; i <= ps.sz; i++) {
    int p = ps.fail[i];
    if (p <= 1) continue;
    int l = ps.pos[i] - (ps.len[i] - ps.len[p]) + 1;
    int r = ps.pos[i];
    ull h = hs.query(l, r);
    if (mpt.count(h)) ans -= mpt[h];

    int plen = checkDec(l, r, ps, psr);
    if (plen != -1) {
      ull pw = hs.query(l, l + plen - 1);
      ull wt = offset(h, pw, plen);
      if (padmpt.count(pw) && padmpt.count(wt)) {
        ans--;
      }
    }
  }

  for (int i = 2; i <= pt.sz; i++) {
    int p = pt.fail[i];
    if (p <= 1) continue;
    int l = pt.pos[i] - pt.len[i] + 1;
    int r = l + (pt.len[i] - pt.len[p]) - 1;
    ull h = ht.query(l, r);
    if (mps.count(h)) ans -= mps[h];

    int plen = checkDec(l, r, pt, ptr);
    if (plen != -1) {
      ull pw = ht.query(l + plen, r);
      ull tw = offset(pw, h, r - l + 1);
      if (padmps.count(pw) && padmps.count(tw)) {
        ans--;
      }
    }
  }

  for (int i = 2; i <= ps.sz; i++) {
    int p = ps.fail[i];
    if (p <= 1) continue;
    if (ps.len[i] > ps.len[p] * 2) {
      int l = ps.pos[i] - (ps.len[i] - ps.len[p]) + 1;
      int r = ps.pos[i];
      mps[hs.query(l, r)]++;
    }
  }

  for (int i = 2; i <= pt.sz; i++) {
    int p = pt.fail[i];
    if (p <= 1) continue;
    if (pt.len[i] > pt.len[p] * 2) {
      int l = pt.pos[i] - pt.len[i] + 1;
      int r = l + (pt.len[i] - pt.len[p]) - 1;
      mpt[ht.query(l, r)]++;
    }
  }

  for (auto& x: mps) {
    ans += 1ll * x.second * mpt[x.first];
  }

  printf("%I64d\n", ans);
  return 0;
}