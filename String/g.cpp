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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

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
  ll count() {
    for (int i = sz; i >= 0; i--) {
      cnt[fail[i]] += cnt[i];
    }
    ll ans = 0;
    for (int i = 2; i <= sz; i++) {
      ans += 1ll * cnt[i] * (cnt[i] - 1) / 2;
      ans %= mod;
    }
    return ans;
  }
}

char s[maxn];

int main() {
  pam::clear();
  scanf("%s", s);
  for (int i = 0; s[i]; i++) {
    pam::insert(s[i]);
  }
  cout << pam::count();
  return 0;
}