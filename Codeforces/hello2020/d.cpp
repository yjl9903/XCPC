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
#include <random>
#include <ctime>
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
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> PII;
const int mod = 998244353;
const ll inf = 1e18;
const int maxn = 100000 + 5;

mt19937_64 rnd(time(nullptr));

struct Seg {
  int l, r, id;
  bool operator<(const Seg& b) const {
    return l < b.l;
  }
};

int n, ed[2][maxn];
ull val[maxn], ck[maxn];
vector<int> lsh;

int gid(int x) {
  return lower_bound(begin(lsh), end(lsh), x) - begin(lsh) + 1;
}

struct BIT {
  ull a[maxn * 4];
  void clear() {
    ms(a, 0);
  }
  void update(int i, ull x) {
    for (; i <= 4 * maxn - 1; i += i & -i) a[i] ^= x;
  }
  ull query(int i) {
    ull r = 0;
    for (; i; i -= i & -i) r ^= a[i];
    return r;
  }
  ull query(int l, int r) {
    return query(r) ^ query(l - 1);
  }
} h[2];

void solve(vector<Seg>& a) {
  h[0].clear(); h[1].clear();
  sort(begin(a), end(a));
  for (int i = 0; i < n; i++) {
    h[0].update(a[i].l, val[a[i].id]);
    h[1].update(a[i].r, val[a[i].id]);
  }
  for (int i = 0; i < n; i++) {
    int id = a[i].id;
    int l = a[i].l, r = a[i].r;
    if (l > 1) ck[id] ^= h[1].query(1, l - 1);
    ck[id] ^= h[0].query(r + 1, 4 * maxn - 1);
  }
}

int main() {
  scanf("%d", &n);
  vector<Seg> a, b;
  for (int i = 1; i <= n; i++) {
    val[i] = rnd();
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    a.push_back({ x1, y1, i });
    b.push_back({ x2, y2, i });
    lsh.push_back(x1); lsh.push_back(y1);
    lsh.push_back(x2); lsh.push_back(y2);
  }
  sort(begin(lsh), end(lsh));
  lsh.resize(unique(begin(lsh), end(lsh)) - begin(lsh));
  for (auto& x: a) x.l = gid(x.l), x.r = gid(x.r);
  for (auto& x: b) x.l = gid(x.l), x.r = gid(x.r);
  solve(a); solve(b);
  for (int i = 1; i <= n; i++) if (ck[i]) return puts("NO"), 0;
  puts("YES");
  return 0;
}