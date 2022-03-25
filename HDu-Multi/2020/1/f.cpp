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
const int maxn = 100000 + 5;

int n, m, q, a[maxn];
vector<int> edge[maxn], bEdge[maxn];

struct Block {
  int V, Bsize, Bcnt;
  vector<int> cnt, bel, blkC;
  vector<PII> rg;

  void build(int u) {
    V = (int)edge[u].size() + 2;
    Bsize = sqrt(V + 0.5);
    Bcnt = 0;
    cnt.assign(V + 1, 0);
    bel.assign(V + 1, 0);
    rg.clear();
    blkC.clear();

    for (int i = 0; i <= V; i += Bsize, Bcnt++) {
      for (int j = i; j < i + Bsize && j <= V; j++) {
        bel[j] = Bcnt;
      }
      rg.emplace_back(i, min(i + Bsize - 1, V));
      blkC.push_back(0);
    }
  }

  void ins(int x) {
    if (x > V) return ;
    cnt[x]++;
    if (cnt[x] == 1) {
      blkC[bel[x]]++;
    }
  }

  void del(int x) {
    if (x > V) return ;
    cnt[x]--;
    if (cnt[x] == 0) {
      blkC[bel[x]]--;
    }
  }

  int query() {
    for (int i = 0; i < Bcnt; i++) {
      if (rg[i].second - rg[i].first + 1 > blkC[i]) {
        for (int j = rg[i].first; j <= rg[i].second; j++) {
          if (cnt[j] == 0) {
            return j;
          }
        }
      }
    }
    return V + 1;
  }
} blk[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);

    int DegSz = sqrt(n + 0.5);

    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      edge[i].clear();
      bEdge[i].clear();
    }
    for (int i = 1, u, v; i <= m; i++) {
      scanf("%d%d", &u, &v);
      edge[u].push_back(v);
      edge[v].push_back(u);
    }

    for (int u = 1; u <= n; u++) {
      blk[u].build(u);
      for (int v: edge[u]) {
        if ((int)edge[v].size() > DegSz) {
          bEdge[u].push_back(v);
        } else {
          blk[u].ins(a[v]);
        }
      }
    }

    scanf("%d", &q);
    int op, u, x;
    while (q--) {
      scanf("%d%d", &op, &u);
      if (op == 1) {
        scanf("%d", &x);
        if (edge[u].size() <= DegSz) {
          for (int v: edge[u]) {
            blk[v].del(a[u]);
            blk[v].ins(x);
          }
        }
        a[u] = x;
      } else if (op == 2) {
        for (int v: bEdge[u]) {
          blk[u].ins(a[v]);
        }
        printf("%d\n", blk[u].query());
        for (int v: bEdge[u]) {
          blk[u].del(a[v]);
        }
      }
    }
  }
  return 0;
}