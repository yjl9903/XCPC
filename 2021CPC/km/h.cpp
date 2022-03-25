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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

char id(char ch) {
  if (ch == 'A') return 'a';
  else if (ch == 'C') return 'b';
  else if (ch == 'G') return 'c';
  else if (ch == 'U') return 'd';
  assert(false);
}

int q, V[5], node[maxn];

namespace pam {
  static const int S = 4;

  int sz, tot;
  int len[maxn], ch[maxn][S], go[maxn][S];
  int fail[maxn], link[maxn][20];
  int cnt[maxn], dep[maxn], val[maxn], mx[maxn];
  char s[maxn];

  int node(int l) {
    sz++;
    ms(ch[sz], 0);
    len[sz] = l;
    fail[sz] = cnt[sz] = 0;
    return sz;
  }
  void clear() {
    sz = -1;
    s[tot = 0] = '$';
    node(0);
    node(-1);
    fail[0] = 1;
    for (int i = 0; i < S; i++) {
      go[0][i] = 1;
    }
  }
  int jump(int tot, int len) {
    for (int j = 19; j >= 0; j--) {
      int u = link[tot][j];
      if (dep[u] >= len) {
        tot = u;
      }
    }
    return tot;
  }
  int getfail(int x) {
    if (s[tot] == s[jump(tot, dep[tot] - len[x] - 1)]) {
      return x;
    } else {
      return go[x][s[tot] - 'a'];
    }
  }
  int insert(char c, int fa, int last = 0) {
    s[++tot] = c;
    dep[tot] = dep[fa] + 1;
    link[tot][0] = fa;
    for (int i = 1; i < 20; i++) {
      link[tot][i] = link[link[tot][i - 1]][i - 1];
    }
    int now = getfail(last);
    if (!ch[now][c - 'a']) {
      int x = node(len[now] + 2);
      fail[x] = ch[getfail(fail[now])][c - 'a'];
      ch[now][c - 'a'] = x;

      if (len[x] == 1) val[x] = V[s[tot] - 'a'];
      else val[x] = val[now] + 2 * V[s[tot] - 'a'];
      mx[x] = max(val[x], mx[fail[x]]);

      memcpy(go[x], go[fail[x]], sizeof go[x]);
      go[x][s[jump(tot, dep[tot] - len[fail[x]])] - 'a'] = fail[x];
    }
    last = ch[now][c - 'a'];
    cnt[last]++;
    return last;
  }
  int count() {
    int ans = 0;
    for (int i = sz; i >= 0; i--) {
      cnt[fail[i]] += cnt[i];
    }
    for (int i = 2; i <= sz; i++) {
      ans = (ans + 1ll * cnt[i] * val[i] % mod) % mod;
    }
    return ans;
  }
}

int main() {
  pam::clear();
  for (int i = 0; i < 4; i++) {
    scanf("%d", V + i);
  }
  char ch[2];
  scanf("%s", ch);
  node[1] = pam::insert(id(ch[0]), 0);
  int ans = pam::mx[node[1]];
  printf("%d\n", ans);
  for (q = 2; ; q++) {
    int fa;
    if (scanf("%d%s", &fa, ch) == 2) {
      fa ^= ans;
      if (fa == 0) break;
      int u = pam::insert(id(ch[0]), fa, node[fa]);
      node[q] = u;
      printf("%d\n", ans = pam::mx[u]);
    } else {
      assert(false);
      break;
    }
  }
  printf("%d\n", pam::count());
  return 0;
}