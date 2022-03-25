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
const int maxn = 500000 + 5;
const int maxm = 1000000 + 5;

int n, q, nn;
vector<int> lsh;

int gid(int x) {
  return lower_bound(begin(lsh), end(lsh), x) - begin(lsh) + 1;
}

namespace PSegT {
  #define lson l, m, ls[rt]
  #define rson m + 1, r, rs[rt]
  int tot, root[maxn], ls[maxn * 150], rs[maxn * 150];
  int mx[maxn * 150], mn[maxn * 150];

  void clear() {
    for (int i = 1; i <= n; i++) {
      root[i] = 0;
    }
    for (int i = 0; i <= tot; i++) {
      ls[i] = rs[i] = 0;
      mx[i] = mn[i] = -1;
    }
    tot = 0;
  }
  
  void update(int i, int x, int l, int r, int& rt) {
    if (!rt) rt = ++tot;
    if (l == r) {
      mx[rt] = mn[rt] = x; return ;
    }
    int m = (l + r) / 2;
    if (i <= m) update(i, x, lson);
    else update(i, x, rson);
    if (mx[rt] == -1 || mx[rt] < x) mx[rt] = x;
    if (mn[rt] == -1 || mn[rt] > x) mn[rt] = x;
  }
  inline void update(int i, int pos, int val) {
    for (; i <= n; i += i & -i) update(pos, val, 1, nn, root[i]);
  }

  vector<int> L, R;
  int qmx(int i, int l, int r, int rt) {
    // if (l == r) {
    //   int sum = 0;
    //   for (int x: L) sum -= cnt[x];
    //   for (int x: R) sum += cnt[x];
    //   return sum;
    // }
    // int m = (l + r) / 2;
    // if (i <= m) {
    //   for (int& x: L) x = ls[x];
    //   for (int& x: R) x = ls[x];
    //   return query(i, l, m, 1);
    // } else {
    //   ll sum = 0;
    //   for (int& x: L) sum -= cnt[ls[x]], x = rs[x];
    //   for (int& x: R) sum += cnt[ls[x]], x = rs[x];
    //   return sum + query(i, m + 1, r, 1);
    // }
    if (l == r) {
      
    }
  }
  int qmn(int i, int l, int r, int rt) {

  }
  
  inline int query(int l, int r, int k) {
    L.clear(); R.clear();
    for (int i = l - 1; i; i -= i & -i) L.push_back(root[i]);
    for (int i = r; i; i -= i & -i) R.push_back(root[i]);
    // return query(k, 1, nn, 1);
  }

  inline int solve(int l, int r, int h) {

  }
}

namespace BIT {
  int a[maxn];
  void clear() {
    for (int i = 1; i <= n; i++) a[i] = 0;
  }
  void update(int i, int x) {
    for (; i <= n + 1; i += i & -i) a[i] += x;
  }
  int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += a[i];
    return r;
  }
  int query(int l, int r) {
    return query(r) - query(l - 1);
  }
}

struct Query {
  int op, h, x, y;
} que[maxm];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &q);
    PSegT::clear();
    lsh.clear();
    for (int t = 1; t <= q; t++) {
      scanf("%d", &que[t].op);
      if (que[t].op == 0) {
        scanf("%d%d", &que[t].x, &que[t].h);
      } else if (que[t].op == 1) {
        scanf("%d%d%d", &que[t].x, &que[t].y, &que[t].h);
      }
      lsh.push_back(que[t].h);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(begin(lsh), end(lsh)) - begin(lsh));
    nn = (int)lsh.size();
    for (int t = 1; t <= q; t++) {
      if (que[t].op == 0) {
        BIT::update(que[t].x, 1);
        PSegT::update(que[t].x, gid(que[t].h), 1);
      } else if (que[t].op == 1) {
        if (BIT::query(que[t].x, que[t].y) == 0) {
          puts("-1"); continue;
        }
        printf("%d\n", PSegT::solve(que[t].x, que[t].y, que[t].h));
      }
    }
  }
  return 0;
}