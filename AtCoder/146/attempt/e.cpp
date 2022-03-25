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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 600000 + 5;

int n, k, b[maxn];
ll a[maxn];

int update(int i, int x = 1) {
  for (; i < maxn; i += i & -i) b[i] += x;
}
int query(int i) {
  int r = 0;
  for (; i; i -= i & -i) r += b[i];
  return r;
}
int query(int l, int r) {
  if (l > r) return 0;
  return query(r) - query(l - 1);
}

int main() {
  scanf("%d%d", &n, &k);
  vector<ll> lsh(1, 0);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    a[i] += a[i - 1];
    lsh.push_back(a[i] % k);
    // lsh.push_back(a[i] % k);
  }
  sort(begin(lsh), end(lsh));
  lsh.resize(unique(begin(lsh), end(lsh)) - begin(lsh));
  auto gid = [&](ll x) {
    return lower_bound(begin(lsh), end(lsh), x) - begin(lsh) + 1;
  };
  update(gid(0));
  // (pre(r) - pre(l)) % k == r - l
  // pre(r) % k > pre(l) % k => pre(r) % k - r = pre(l) % k - l
  // pre(r) % k < pre(l) % k => pre(r) % k + k - r = pre(l) % k - l
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    
  }
  printf("%lld\n", ans);
  return 0;
}