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

struct BIT {
  static const int R = 1 << 21;
  int a[R];
  inline int lowbit(int x) { return x & -x; }
  void insert(int i) {
    for (; i < R; i += lowbit(i)) a[i]++;
  }
  int findx(int p, int rk) {
    // if (p > R) return -1;
    if (p & 1) {
      // if (p + (a[p] < rk) > R) return -1;
      return p + (a[p] < rk);
    } else {
      if (rk > a[p]) return findx(p + lowbit(p) / 2, rk - a[p]);
      else return findx(p - lowbit(p) / 2, rk);
    }
  }
  int findx(int rk) {
    return findx(R >> 1, rk);
  }
} f;

int n, q, b[maxn], ans[maxn];
PII a[maxn];
vector<PII> que[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", b + i);
    a[i].first = b[i];
    a[i].second = i;
  }
  sort(a + 1, a + 1 + n, [](PII a, PII b) {
    if (a.first != b.first) return a.first > b.first;
    return a.second < b.second;
  });
  scanf("%d", &q);
  for (int i = 1, k, pos; i <= q; i++) {
    scanf("%d%d", &k, &pos);
    que[k].emplace_back(pos, i);
  }
  for (int i = 1; i <= n; i++) {
    f.insert(a[i].second);
    for (auto& x: que[i]) {
      ans[x.second] = b[f.findx(x.first)];
    }
  }
  for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
  return 0;
}