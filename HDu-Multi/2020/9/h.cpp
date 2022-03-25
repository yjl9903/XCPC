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
const int maxn = 200000 + 5;
const int Bsz = 500;

int n, q;
unsigned int ans[maxn];
vector<PII> edge[maxn];

struct Query {
  int l, r, id;
  
  bool operator<(const Query& b) const {
    if (l / Bsz != b.l / Bsz) {
      return l < b.l;
    } else {
      return l / Bsz % 2 ? r > b.r : r < b.r;
    }
  }
} a[maxn];



int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
      edge[i].clear();
    }
    for (int i = 2, u, v, w; i <= n; i++) {
      scanf("%d%d%d", &u, &v, &w);
      edge[u].emplace_back(v, w);
      edge[v].emplace_back(u, w);
    }



    for (int i = 1; i <= q; i++) {
      int L, R;
      scanf("%d%d", &L, &R);
      a[i] = Query { L, R, i };
    }
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= q; i++) {

    }

    for (int i = 1; i <= q; i++) {
      printf("%u\n", ans[i]);
    }
  }
  return 0;
}