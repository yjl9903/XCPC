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
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using ull = unsigned long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

ull k1, k2;
ull gen() {
  ull k3 = k1, k4 = k2;
  k1 = k4;
  k3 ^= k3 << 23;
  k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
  return k2 + k4;
}

struct Node {
  ull x, y; int z, id;

  bool operator< (const Node& b) const {
    if (y == b.y) return z < b.z;
    return y < b.y;
  }
} a[maxn], b[maxn];

struct BIT {
  int a[maxn];
  void ins(int i, int x) {
    for (; i < maxn; i += i & -i) a[i] = max(a[i], x);
  }
  void del(int i) {
    for (; i < maxn; i += i & -i) a[i] = 0;
  }
  int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r = max(r, a[i]);
    return r;
  }
} f;

int n, ans[maxn];
ull z[maxn];

void cdq(int l, int r) {
  if (l >= r) return;
  int m = (l + r) / 2;
  cdq(l, m);
  for (int i = l; i <= r; i++) b[i] = a[i];
  sort(b + l, b + m + 1);
  sort(b + m + 1, b + r + 1);
  int j = l;
  for (int i = m + 1; i <= r; i++) {
    for (; j <= m && b[j].y <= b[i].y; j++) f.ins(b[j].z, 1 + ans[b[j].id]);
    ans[b[i].id] = max(ans[b[i].id], f.query(b[i].z));
  }
  for (j--; j >= l; j--) f.del(b[j].z);
  cdq(m + 1, r);
}

int main() {
  scanf("%d%llu%llu", &n, &k1, &k2);
  vector<ull> lsh;
  for (int i = 1; i <= n; i++) {
    a[i].x = gen();
    a[i].y = gen();
    z[i] = gen();
    // dbg(a[i].x, a[i].y, z[i]);
    lsh.push_back(z[i]);
  }
  sort(begin(lsh), end(lsh));
  lsh.resize(unique(begin(lsh), end(lsh)) - begin(lsh));
  for (int i = 1; i <= n; i++) {
    a[i].z = lower_bound(begin(lsh), end(lsh), z[i]) - begin(lsh) + 1;
    a[i].id = i;
  }
  sort(a + 1, a + 1 + n, [](const Node& a, const Node& b) {
    if (a.x != b.x) return a.x < b.x;
    else if (a.y != b.y) return a.y < b.y;
    return a.z < b.z;
  });
  cdq(1, n);
  int mx = 0;
  for (int i = 1; i <= n; i++) {
    mx = max(mx, ans[i]);
  }
  printf("%d\n", mx + 1);
  for (int i = 1; i <= n; i++) {
    printf("%d ", ans[i]);
  }
  return 0;
}