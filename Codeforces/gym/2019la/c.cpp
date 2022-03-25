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
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;
const int maxm = 1000000 + 5;

vector<ll> lsh;
int gid(ll x) {
  return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
}

int n, q, L, U, a[maxn], ans[maxn];
ll pre[maxn];

namespace PSegT {
  int tot, root[maxn], ls[maxn * 40], rs[maxn * 40], pos[maxn * 40];
  void update(int i, int x, int pre, int l, int r, int& rt) {
    rt = ++tot; ls[rt] = ls[pre]; rs[rt] = rs[pre];
    pos[rt] = min(pre == 0 ? n + 1 : pos[pre], x);
    if (l == r) return ;
    int m = (l + r) / 2;
    if (i <= m) update(i, x, ls[pre], lson);
    else update(i, x, rs[pre], rson);
  }
  int query(int L, int R, int l, int r, int rt) {
    if (!rt) return n + 1;
    if (L <= l && r <= R) return pos[rt];
    int m = (l + r) / 2, ans = n + 1;
    if (L <= m) ans = min(ans, query(L, R, lson));
    if (R > m) ans = min(ans, query(L, R, rson));
    return ans;
  }
}

namespace PSegT2 {
  int tot, root[maxn][2], ls[maxn * 80], rs[maxn * 80];
  PII val[maxn * 80];
  void update(int i, int x, int pre, int l, int r, int& rt) {
    rt = ++tot; ls[rt] = ls[pre]; rs[rt] = rs[pre];
    if (pre == 0) val[rt] = { i, x };
    else {
      val[rt] = max((PII){i, x}, val[pre]);
    }
    if (l == r) return ;
    int m = (l + r) / 2;
    if (i <= m) update(i, x, ls[pre], lson);
    else update(i, x, rs[pre], rson);
  }
  PII query(int i, int l, int r, int rt) {
    if (!rt) return {-1, -1};
    if (l == r) {
      return val[rt];
    }
    int m = (l + r) / 2;
    if (i <= m) return query(i, lson);
    else return max(val[ls[rt]], query(i, rson));
  }
}

int main() {
  scanf("%d%d%d", &n, &L, &U);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    pre[i] = pre[i - 1] + a[i];
    lsh.push_back(pre[i]);
  }

  sort(lsh.begin(), lsh.end());
  lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
  int nn = (int)lsh.size() + 1;
  
  for (int i = n; i >= 1; i--) {
    int id = gid(pre[i]);
    PSegT::update(id, i, PSegT::root[i + 1], 1, nn, PSegT::root[i]);

    int up = gid(pre[i]);
    int pu = PSegT::query(up, nn, 1, nn, PSegT::root[i + 1]);
    int lo = gid(pre[i] - (U - L));
    if (lsh[lo - 1] > pre[i] - (U - L)) lo--;
    int pl = lo <= 0 ? n + 1 : PSegT::query(1, lo, 1, nn, PSegT::root[i + 1]);

    if (pu < pl) {
      PSegT2::update(i, 1, PSegT2::root[pu][0], 1, n, PSegT2::root[i][0]);
    } else {
      PSegT2::update(i, 1, PSegT2::root[pl][1], 1, n, PSegT2::root[i][0]);
    }

    up = gid(pre[i] + (U - L));
    pu = PSegT::query(up, nn, 1, nn, PSegT::root[i + 1]);
    lo = gid(pre[i]);
    if (lsh[lo - 1] > pre[i]) lo--;
    pl = lo <= 0 ? n + 1 : PSegT::query(1, lo, 1, nn, PSegT::root[i + 1]);

    if (pu < pl) {
      PSegT2::update(i, 2, PSegT2::root[pu][0], 1, n, PSegT2::root[i][1]);
    } else {
      PSegT2::update(i, 2, PSegT2::root[pl][1], 1, n, PSegT2::root[i][1]);
    }
  }
  
  scanf("%d", &q);
  for (int i = 1, l, r, x; i <= q; i++) {
    scanf("%d%d%d", &l, &r, &x);

    int up = gid(pre[l - 1] + (U - x));
    int pu = PSegT::query(up, nn, 1, nn, PSegT::root[l]);
    int lo = gid(pre[l - 1] - (x - L));
    if (lsh[lo - 1] > pre[l - 1] - (x - L)) lo--;
    int pl = lo <= 0 ? n + 1 : PSegT::query(1, lo, 1, nn, PSegT::root[l]);

    auto solveU = [&]() {
      auto que = PSegT2::query(r, 1, n, PSegT2::root[pu][0]);
      assert(que.first != -1 && que.second != -1);
      int last = que.first;
      if (que.second == 1) {
        printf("%lld\n", U + (pre[r] - pre[last]));
      } else if (que.second == 2) {
        printf("%lld\n", L + (pre[r] - pre[last]));
      }
    };
    auto solveL = [&]() {
      auto que = PSegT2::query(r, 1, n, PSegT2::root[pl][1]);
      assert(que.first != -1 && que.second != -1);
      int last = que.first;
      if (que.second == 1) {
        printf("%lld\n", U + (pre[r] - pre[last]));
      } else if (que.second == 2) {
        printf("%lld\n", L + (pre[r] - pre[last]));
      }
    };

    if (pu > r && pl > r) {
      printf("%lld\n", x + pre[r] - pre[l - 1]);
    } else if (pu > r) {
      solveL();
    } else if (pl > r) {
      solveU();
    } else {
      if (pu < pl) solveU();
      else solveL();
    }
  }
  return 0;
}