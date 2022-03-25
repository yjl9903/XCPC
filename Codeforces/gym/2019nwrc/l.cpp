#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
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
const int maxn = 200000 + 5;

PII ans = {1, 1};
bool gt(PII a, PII b) {
  return 1ll * a.first * b.second > 1ll * a.second * b.first;
}

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

  set<PII> mp;
  void add(int l, int r, int p) {
    if (mp.count({l, r})) return ;
    // Run => (l, r, p)
    mp.insert({l, r});
    // ans.push_back({r - l + 1, p});
    if (gt({r - l + 1, p}, ans)) {
      ans = {r - l + 1, p};
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
  void build(int nn, char* ss) {
    n = nn;
    for (int i = 1; i <= n; i++) s[i] = ss[i];
    s[n + 1] = 0;
    ori.build(n, ss); // 原串
    reverse(ss + 1, ss + n + 1);
    rev.build(n, ss); // 反串
    mp.clear();
    find(0); find(1);
  }
}

namespace sam {
  int sz, last, cnt[maxn << 1];
  int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];
  void clear() { 
    for (int i = 1; i <= sz; i++) {
      len[i] = link[i] = cnt[i] = 0;
      ms(ch[i], 0);
    }
    sz = last = 1;
  }
  int insert(int c) {
    int cur = ++sz, p = last; 
    len[cur] = len[last] + 1; 
    cnt[cur] = 1;
    for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
    if (!p) link[cur] = 1;
    else {
      int q = ch[p][c];
      if (len[p] + 1 == len[q]) link[cur] = q;
      else {
        int nq = ++sz; 
        len[nq] = len[p] + 1; 
        link[nq] = link[q]; 
        link[q] = link[cur] = nq;
        memcpy(ch[nq], ch[q], sizeof ch[q]);
        for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
      }
    }
    return last = cur;
  }
  vector<int> edge[maxn << 1];
  set<int> eds[maxn << 1];
  void dfs(int u) {
    for (int v: edge[u]) {
      dfs(v);
      if (!len[u]) continue;
      if ((int)eds[u].size() < (int)eds[v].size()) swap(eds[u], eds[v]);
      for (int p: eds[v]) {
        auto it = eds[u].upper_bound(p);
        if (it != eds[u].end()) {
          // upd[*it].push_back({p, len[u]});
          PII tot = { len[u] + *it - p, *it - p };
          if (gt(tot, ans)) {
            ans = tot;
          }
        }
        if (it != eds[u].begin()) {
          it--;
          // upd[p].push_back({*it, len[u]});
          PII tot = { len[u] + p - *it, p - *it };
          if (gt(tot, ans)) {
            ans = tot;
          }
        }
      }
      for (int p: eds[v]) eds[u].insert(p);
    }
  }
  void solve(int n, char* s) {
    clear();
    for (int i = 1; i <= n; i++) {
      int cur = insert(s[i] - 'a');
      eds[cur].insert(i);
    }
    for (int i = 2; i <= sz; i++) edge[link[i]].push_back(i);
    dfs(1);
  }
}

char s[maxn];
int n;

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  Runs::build(n, s);
  int len = ans.first, p = ans.second;
  if (len == 1 && p == 1) {
    sam::solve(n, s);
    len = ans.first, p = ans.second;
  }
  int g = __gcd(len, p);
  printf("%d/%d\n", len / g, p / g);
  return 0;
}