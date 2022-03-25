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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 400000 + 5;

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
  void count() {
    for (int i = sz; i >= 2; i--) {
      cnt[fail[i]] += cnt[i];
    }
  }
} p1, p2;

char s[maxn], t[maxn];

ll ans;
void dfs(int x, int y) {
  for (int c = 0; c < 26; c++) {
    if (p1.ch[x][c] && p2.ch[y][c]) {
      ans += 1ll * p1.cnt[p1.ch[x][c]] * p2.cnt[p2.ch[y][c]];
      dfs(p1.ch[x][c], p2.ch[y][c]);
    }
  }
}

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    p1.clear(); p2.clear();
    scanf("%s", s);
    for (int i = 0; s[i]; i++) p1.insert(s[i]);
    p1.count();
    scanf("%s", t);
    for (int i = 0; t[i]; i++) p2.insert(t[i]);
    p2.count();
    ans = 0;
    dfs(0, 0); dfs(1, 1);
    printf("Case #%d: %lld\n", ++kase, ans);
  }
  return 0;
}