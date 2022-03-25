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
const int maxn = 1000000 + 5;

int n, le[maxn], ri[maxn];
PII a[maxn];

struct BIT {
  int b[maxn];
  void update(int i, int x) {
    for (; i < maxn; i += i & -i) b[i] += x;
  }
  int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += b[i];
    return r;
  }
} f, g;

int main() {
  scanf("%d", &n);
  vector<PII> evs;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].first, &a[i].second);
    evs.push_back({a[i].first, 1});
    evs.push_back({a[i].second, -1});
    le[a[i].second] = a[i].first;
    ri[a[i].first] = a[i].second;
  }
  sort(begin(evs), end(evs));
  ll tot = 0; int flag = 1;
  for (auto& ev: evs) {
    if (ev.second == 1) {
      tot += f.query(ri[ev.first]);
      f.update(ri[ev.first], 1);
      g.update(maxn - ev.first, 1);
    } else if (ev.second == -1) {
      tot -= g.query(maxn - le[ev.first]) - 1;
      if (tot) {
        flag = 0;
      }
      f.update(ev.first, -1);
      g.update(maxn - le[ev.first], -1);
    }
    dbg(ev.first, ev.second, tot);
  }
  if (flag) puts("YES");
  else puts("NO");
  return 0;
}