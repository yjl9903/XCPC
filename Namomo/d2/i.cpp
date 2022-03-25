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
const ll inf = 1ll << 60;
const int maxn = 2000 + 5;
const int maxq = 200000 + 5;

struct Node {
  int l, r, id;
  ll val;

  bool operator < (const Node& rhs) const {
    if (val == rhs.val) {
      return id < rhs.id;
    }
    return val < rhs.val;
  }
};

int n, q, a[maxn];

ll b[maxn][maxn], ans[maxq];
void update(int x, int y, ll val) {
  for (int i = x; i; i -= i & -i) {
    for (int j = y; j <= n; j += j & -j) {
      b[i][j] = max(b[i][j], val);
    }
  }
}
ll query(int x, int y) {
  ll ans = -inf;
  for (int i = x; i <= n; i += i & -i) {
    for (int j = y; j; j -= j & -j) {
      ans = max(ans, b[i][j]);
    }
  }
  return ans;
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  vector<Node> evs;
  for (int i = 1; i <= n; i++) {
    ll sum = 0;
    for (int j = i; j <= n; j++) {
      sum += a[j];
      evs.push_back(Node { i, j, 0, sum });
    }
    for (int j = 1; j <= n; j++) {
      b[i][j] = -inf;
    }
  }
  for (int i = 1; i <= q; i++) {
    int l, r; ll v;
    scanf("%d%d%lld", &l, &r, &v);
    evs.push_back(Node { l, r, i, v });
  }
  sort(evs.begin(), evs.end());
  for (auto& ev: evs) {
    if (ev.id == 0) {
      update(ev.l, ev.r, ev.val);
    } else {
      ans[ev.id] = query(ev.l, ev.r);
    }
  }
  for (int i = 1; i <= q; i++) {
    if (ans[i] == -inf) {
      puts("NONE");
    } else {
      printf("%lld\n", ans[i]);
    }
  }
  return 0;
}