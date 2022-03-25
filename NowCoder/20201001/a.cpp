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
const int maxn = 400000 + 5;

namespace pam {
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
  int insert(char c) {
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
    return last;
  }
  void count() {
    for (int i = sz; i >= 0; i--) {
      cnt[fail[i]] += cnt[i];
    }
  }
}

int n;
char s[maxn];

int main() {
  scanf("%d%s", &n, s + 1);
  pam::clear();
  for (int i = 1; i < n; i++) {
    pam::insert(s[i]);
  }
  int u = pam::insert(s[n]);
  printf("%d\n", n - pam::len[u]);
  return 0;
}