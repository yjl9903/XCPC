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
  void rsort() {
    for (int i = 1; i <= sz; i++) c[i] = 0;
    for (int i = 1; i <= sz; i++) c[len[i]]++;
    for (int i = 1; i <= sz; i++) c[i] += c[i - 1];
    for (int i = 1; i <= sz; i++) a[c[len[i]]--] = i;
    for (int i = sz; i; i--) {
      int p = a[i];
      cnt[link[p]] += cnt[p];
    }
  }
}
using sam::ch;
using sam::len;
using sam::link;

int n, q, dp[maxn];
char s[maxn];

int main() {
  sam::clear();
  scanf("%s%d", s + 1, &q);
  n = strlen(s + 1);
  for (int i = 1; i <= n; i++) {
    sam::insert(s[i] - 'A');
  }
  while (q--) {
    scanf("%s", s + 1);
    int u = 1, l = 0, m = strlen(s + 1);
    for (int i = 0; i <= m; i++) dp[i] = 0;
    for (int i = 1; i <= m; i++) {
      int c = s[i] - 'A';
      if (ch[u][c]) u = ch[u][c], l++;
      else {
        while (u && !ch[u][c]) u = link[u];
        if (!u) u = 1, l = 0;
        else l = len[u] + 1, u = ch[u][c];
      }
      if (l) {
        dp[i] = dp[i - l] + 1;
      } else {
        dp[m] = 0;
        break;
      }
    }
    if (dp[m] == 0) puts("-1");
    else printf("%d\n", dp[m]);
  }
  return 0;
}