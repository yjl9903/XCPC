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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n;
char t[maxn], s[maxn];

struct pam {
  int sz, tot, last;
  int ch[maxn][26], len[maxn], fail[maxn];
  int cnt[maxn], dep[maxn];
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
  void insert(char c) {
    s[++tot] = c;
    int now = getfail(last);
    if (!ch[now][c - 'a']) {
      int x = node(len[now] + 2);
      fail[x] = ch[getfail(fail[now])][c - 'a'];
      dep[x] = dep[fail[x]] + 1;
      ch[now][c - 'a'] = x;
    }
    last = ch[now][c - 'a'];
    cnt[last]++;
  }
  int fa[21][maxn];
  void build() {
    for (int i = 1; i <= sz; i++) {
      fa[0][i] = fail[i];
    }
    for (int j = 1; j < 20; j++) {
      for (int i = 1; i <= n; i++) {
        fa[j][i] = fa[j - 1][fa[j - 1][i]];
      }
    }
  }
  int query(int u, int l) {
    int ans = dep[u];
    for (int i = 20; i >= 0; i--) {
      if (len[fa[i][u]] > l) {
        ans -= 1 << i;
        u = fa[i][u];
      }
    }
    return ans;
  }
} f, g;

int val[30];
int pnd[maxn], snd[maxn];

int main() {
  int n, c, k, p;
  scanf("%d%d%d%d", &n, &c, &k, &p);
  for (int i = 0; i < 26; i++) scanf("%d", val + i);
  scanf("%s%s", t + 1, s + 1);

  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    ll sum = val[t[i] - 'a'] + val[s[i] - 'a'];
    ll tot = 1;
    for (int i = 1; i <= p; i++) tot = tot * sum;
    ans += tot;
  }
  
  f.clear(); g.clear();
  ll asum = 0;
  for (int i = 1; i <= n; i++) {
    f.insert(t[i]);
    asum += f.dep[f.last];
  }

  f.clear();
  ll bsum = 0;
  for (int i = 1; i <= n; i++) {
    f.insert(s[i]);
    bsum += f.dep[f.last];
  }
  if (abs(asum - bsum) <= k) {
    cout << ans;
    return 0;
  }

  for (int i = 1; i <= n; i++) f.insert(s[i]), pnd[i] = f.last;
  f.build();
  for (int i = n; i >= 1; i--) g.insert(s[i]);
  for (int i = n; i >= 1; i--) g.insert(s[i]), snd[i] = g.last;

  for (int i = 1; i <= n; i++) {
    bsum -= g.query(snd[i], n) + f.query(pnd[i], n);
    if (abs(asum - bsum) <= k) {
      ans -= i * c;
      cout << ans << endl;
      return 0;
    }
  }

  puts("0");

  return 0;
}