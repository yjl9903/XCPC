#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <unordered_set>
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
  static void prework() {
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
} h;

template<typename keyT, typename valT>
struct HashTable {
  static const int htMod = (1 << 25) - 1;
  static const int mxSize = maxn << 4;
  keyT key[mxSize]; valT val[mxSize];
  int sz, head[htMod + 10], nxt[mxSize];
  inline void add(int hsh, keyT V) {
    key[++sz] = V;
    nxt[sz] = head[hsh];
    head[hsh] = sz;
  }
  inline valT& operator [](keyT xe) {
    int key = xe & htMod;
    for (int i = head[key]; i; i = nxt[i]) 
      if (this->key[i] == xe) return val[i];
    add(key, xe); return val[sz];
  }
  inline bool count(keyT xe) {
    int key = xe & htMod;
    for (int i = head[key]; i; i = nxt[i])
      if (this->key[i] == xe) return true;
    return false;
  }
  inline void clear() {
    for (int i = 1; i <= sz; i++) head[this->key[i] & htMod] = 0;
    for (int i = 1; i <= sz; i++) val[i] = 0;
    sz = 0;
  }
  inline int size() { return sz; }
};

// set<ull> ps;
HashTable<ull,int> ps;

namespace Runs {
  struct SA {
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
    int dp[21][maxn];
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
      l++; int k = __lg(r - l + 1);
      return min(dp[k][l], dp[k][r - (1 << k) + 1]);
    }
  } ori, rev;
  
  int n; char s[maxn];
  
  bool cmp(int x, int y) {
    int len = ori.qlcp(x, y);
    // if (x + len > n) return false;
    // if (y + len > n) return true;
    return s[x + len] < s[y + len];
  }

  // set<ull> vis;
  HashTable<ull,int> vis;
  void addRuns(int l, int r, int p) {
    ull state = ((1ll * l) << 32) | r;
    if (vis.count(state)) return ;
    // vis.insert(state);
    vis[state] = true;
    // Run => (l, r, p)
    // dbg(l, r, p);
    for (int i = l + 2 * p - 1; i <= r; i++) {
      int x = i - p;
      int len = (x - l + 1) / p * p;
      // ps.insert(h.query(x - len + 1, x));
      ps[h.query(x - len + 1, x)] = true;
    }
    // for (int i = 0; i < p * 2 && l + 2 * p - 1 + i <= r; i++) {
    //   for (int j = l + 2 * p - 1 + i; j <= r; j += 2 * p) {
    //     // Primitive Square: [j-2p+1,j]
    //     ps[h.query(j - 2 * p + 1, j)] = true;
    //   }
    // }
  }
  void checkRuns(int l, int r) {
    int len = r - l;
    int lcp = ori.qlcp(l, r);
    int lcs = rev.qlcp(n - l + 2, n - r + 2);
    if (lcp + lcs >= len) {
      addRuns(l - lcs, r + lcp - 1, len);
    }
  }
  void computeRuns(int type) {
    static int st[maxn], stn;
    stn = 0; st[stn++] = n + 1;
    for (int i = n; i >= 1; i--) {
      while (stn > 1 && cmp(i, st[stn - 1]) == type) stn--;
      checkRuns(i, st[stn - 1]);
      st[stn++] = i;
    }
  }
  void build(int nn, char* ss) {
    n = nn;
    for (int i = 1; i <= n; i++) s[i] = ss[i];
    s[n + 1] = 0;
    ori.build(n, ss + 1);
    reverse(ss + 1, ss + n + 1);
    rev.build(n, ss + 1);
    vis.clear();
    computeRuns(0);
    computeRuns(1);
  }
}

int n; char s[maxn];

int main() {
  Hash::prework();
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    h.build(n, s);
    ps.clear();
    Runs::build(n, s);
    ll ans = 1ll * n * (n + 1) / 2;
    for (int i = 2; i <= n; i++) {
      ans -= Runs::ori.h[i];
    }
    printf("%lld\n", ans - (int)ps.size());
  }
  return 0;
}