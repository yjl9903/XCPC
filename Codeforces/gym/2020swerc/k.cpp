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
const int maxn = 300000 + 5;

int n;
char s[maxn];

namespace sam {
  int sz = 1, last = 1, cnt[maxn << 1], pos[maxn << 1];
  int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];

  int insert(int c, int P) {
    int cur = ++sz, p = last;
    len[cur] = len[last] + 1;
    cnt[cur] = 1;
    pos[cur] = P;
    for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
    if (!p) {
      link[cur] = 1;
    } else {
      int q = ch[p][c];
      if (len[p] + 1 == len[q]) {
        link[cur] = q;
      } else {
        int nq = ++sz;
        len[nq] = len[p] + 1;
        pos[nq] = pos[q];
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
      pos[link[p]] = min(pos[link[p]], pos[p]);
    }
  }

  PII get() {
    PII ans { inf, inf };
    for (int i = 2; i <= sz; i++) {
      if (cnt[i] == 1) {
        ans = min(ans, { len[link[i]] + 1, pos[i] });
      }
    }
    if (ans.first == inf) {
      return { n, n };
    } else {
      return ans;
    }
  }
}

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  for (int i = 1; i <= n; i++) {
    sam::insert(s[i] - 'A', i);
  }
  sam::rsort();
  auto x = sam::get();
  for (int i = x.second - x.first + 1; i <= x.second; i++) {
    putchar(s[i]);
  }
  puts("");
  return 0;
}