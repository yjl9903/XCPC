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
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int m, n, k, t, a[maxn];
vector<PII> bag[maxn];

int tag[maxn];
int check(int x) {
  for (int i = 0; i <= n + 1; i++) tag[i] = 0;
  for (int i = a[x] + 1; i < maxn; i++) {
    for (auto& x: bag[i]) {
      tag[x.first]++;
      tag[x.second + 1]--;
    }
  }
  int ans = n + 1;
  for (int i = 1; i <= n; i++) {
    tag[i] += tag[i - 1];
    if (tag[i]) ans += 2;
  }
  return ans <= t;
}

int main() {
  scanf("%d%d%d%d", &m, &n, &k, &t);
  for (int i = 1; i <= m; i++) {
    scanf("%d", a + i);
  }
  sort(a + 1, a + m + 1, greater<int>());
  for (int i = 1, l, r, x; i <= k; i++) {
    scanf("%d%d%d", &l, &r, &x);
    bag[x].push_back({l, r});
    if (x > a[1]) return puts("0"), 0;
  }
  int l = 1, r = m, ans = 1;
  while (l <= r) {
    int m = (l + r) / 2;
    if (check(m)) l = m + 1, ans = m;
    else r = m - 1;
  }
  cout << ans;
  return 0;
}