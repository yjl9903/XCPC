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
#include <queue>
#include <cassert>
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
const int maxn = 300000 + 5;

int n, q;
char s[maxn];
vector<int> edge[maxn];

int fa[maxn << 1][21];
namespace gsam {
  int tot, last, cnt[maxn << 1];
  int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];
  int insert(int last, int c, int s) {
    int cur = ++tot, p = last;
    ms(ch[cur], 0);
    len[cur] = len[last] + 1;
    cnt[cur] = s;
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
  void clear() {
    tot = last = 1; ms(ch[1], 0);
  }
  vector<int> edge[maxn << 1];
  void build() {
    for (int i = 2; i <= tot; i++) {
      edge[link[i]].push_back(i);
    }
    function<void(int,int)> dfs = [&](int u, int f) {
      fa[u][0] = f;
      for (int i = 1; i < 21; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
      for (int v: edge[u]) dfs(v, u), cnt[u] += cnt[v];
    };
    dfs(1, 0);
  }
}

int get(int u, int l) { // u: s[1...r], l: r - l + 1
  for (int i = 20; i >= 0; i--) {
    if (!fa[u][i]) continue;
    int v = fa[u][i];
    if (gsam::len[v] >= l) u = v;
  }
  return u;
}

namespace Trie {
  int tot, ch[maxn][26], pos[maxn], cnt[maxn];
  void clear() {
    tot = 1;
  }
  void build() {
    queue<int> q; q.push(1);
    pos[1] = 1;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int i = 0; i < 26; i++) {
        if (!ch[u][i]) continue;
        int v = ch[u][i];
        pos[v] = gsam::insert(pos[u], i, cnt[v]);
        q.push(v);
      }
    }
  }
}

int pos2[maxn];
void dfs(int u, int x) {
  pos2[u] = x;
  Trie::cnt[x]++;
  for (int v: edge[u]) {
    int c = s[v] - 'A';
    if (!Trie::ch[x][c]) {
      Trie::ch[x][c] = ++Trie::tot;
    }
    dfs(v, Trie::ch[x][c]);
  }
}

int main() {
  gsam::clear();
  scanf("%d%d%s", &n, &q, s + 1);
  for (int i = 2, fa; i <= n; i++) {
    scanf("%d", &fa);
    edge[fa].push_back(i);
  }
  Trie::ch[1][s[1] - 'A'] = 2;
  Trie::tot = 2;
  dfs(1, 2);
  Trie::build();
  gsam::build();
  while (q--) {
    int x, l; scanf("%d%d", &x, &l);
    x = pos2[x];
    int u = get(Trie::pos[x], l);
    printf("%d\n", gsam::cnt[u]);
  }
  return 0;
}