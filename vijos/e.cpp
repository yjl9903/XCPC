#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <queue>
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
const int maxn = 1000000 + 5;

namespace gsam {
  int tot, last, cnt[maxn << 1];
  int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];
  int insert(int last, int c) {
    int cur = ++tot, p = last;
    ms(ch[cur], 0);
    len[cur] = len[last] + 1;
    cnt[cur] = 1;
    for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
    if (!p) link[cur] = 1;
    else {
      int q = ch[p][c];
      if (len[p] + 1 == len[q]) link[cur] = q;
      else {
        int nq = ++tot;
        len[nq] = len[p] + 1;
        cnt[nq] = 0;
        link[nq] = link[q];
        link[q] = link[cur] = nq;
        memcpy(ch[nq], ch[q], sizeof ch[q]);
        for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
      }
    }
    return cur;
  }
  namespace Trie {
    int tot, ch[maxn][26], pos[maxn];
    void clear() {
      tot = 1;
    }
    void insert(char* s, int& p, int pos[]) {
      int u = 1;
      for (int i = 0; s[i]; i++) {
        int c = s[i] - 'a';
        if (!ch[u][c]) {
          ch[u][c] = ++tot;
          ms(ch[tot], 0);
        }
        u = ch[u][c];
        pos[p++] = u;
      }
    }
    void build() {
      queue<int> q; q.push(1);
      pos[1] = 1;
      while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < 26; i++) {
          if (!ch[u][i]) continue;
          int v = ch[u][i];
          pos[v] = gsam::insert(pos[u], i);
          q.push(v);
        }
      }
    }
  }
  using Trie::insert;

  int fa[21][maxn << 1];
  int c[maxn << 1], a[maxn << 1];
  void build() {
    Trie::build();
    for (int i = 1; i <= tot; i++) c[i] = 0;
    for (int i = 1; i <= tot; i++) c[len[i]]++;
    for (int i = 1; i <= tot; i++) c[i] += c[i - 1];
    for (int i = 1; i <= tot; i++) a[c[len[i]]--] = i;
    for (int i = tot; i; i--) {
      int p = a[i];
      cnt[link[p]] += cnt[p];
      fa[0][p] = link[p];
    }
    for (int i = 1; i <= tot; i++) {
      int p = a[i];
      for (int i = 1; i < 21; i++) {
        fa[i][p] = fa[i - 1][fa[i - 1][p]];
      }
    }
  }
  int get(int u, int l) { // u: s[1...r], l: r - l + 1
    for (int i = 20; i >= 0; i--) {
      if (!fa[i][u]) continue;
      int v = fa[i][u];
      if (len[v] >= l) u = v;
    }
    return u;
  }

  void clear() {
    Trie::clear();
    tot = last = 1; 
    ms(ch[1], 0);
    cnt[1] = len[1] = 0;
  }
}

int n, q, pre[(int)1e5 + 5], pos[maxn];
char s[maxn];

int main() {
  gsam::clear();
  scanf("%d", &n);
  int p = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%s", s);
    pre[i] = pre[i - 1] + strlen(s);
    gsam::insert(s, p, pos);
  }
  gsam::build();
  scanf("%d", &q);
  for (int i = 1, p, x, y; i <= q; i++) {
    scanf("%d%d%d", &p, &x, &y);
    int u = gsam::Trie::pos[pos[pre[p - 1] + y - 1]], len = y - x + 1;
    u = gsam::get(u, len);
    printf("%d\n", gsam::cnt[u]);
  }
  return 0;
}