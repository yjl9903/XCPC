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
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

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
  int c[maxn << 1], a[maxn << 1];
  ll siz[maxn << 1];
  void rsort() {
    for (int i = 1; i <= sz; i++) c[i] = 0;
    for (int i = 1; i <= sz; i++) c[len[i]]++;
    for (int i = 1; i <= sz; i++) c[i] += c[i - 1];
    for (int i = 1; i <= sz; i++) a[c[len[i]]--] = i;
    for (int i = sz; i; i--) {
      int p = a[i];
      cnt[link[p]] += cnt[p];
    }
    for (int i = sz; i; i--) {
      int p = a[i];
      siz[p] += len[p] - len[link[p]];
      siz[link[p]] += siz[p];
    }
    for (int i = 1; i <= sz; i++) {
      dbg(i, siz[i]);
    }
  }
  ll cal(){  
    ll ans = 0;
    for (int i = 1; i <= sz; i++) ans += len[i] - len[link[i]];
    return ans;
  }
}

char s[maxn];

int main() {
  sam::clear();
  scanf("%s", s + 1);
  int n = strlen(s + 1);
  for (int i = 1; i <= n; i++) {
    sam::insert(s[i] - 'a');
  }
  sam::rsort();
  ll sum = sam::cal(), ans = sam::cal();
  for (int i = 1, u = 1; i <= n; i++) {
    u = sam::ch[u][s[i] - 'a'];
    ans += sum - sam::siz[u];
  }
  cout << ans << endl;
  return 0;
}