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

int n, le[maxn], ri[maxn], pre[maxn], id[maxn];
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

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
int join(int x, int y) {
  x = find(x); y = find(y);
  if (x == y) return 0;
  pre[x] = y;
  return 1;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n + n; i++) pre[i] = i;
  vector<PII> evs;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].first, &a[i].second);
    evs.push_back({a[i].first, 1});
    evs.push_back({a[i].second, -1});
    le[a[i].second] = a[i].first;
    ri[a[i].first] = a[i].second;
    id[a[i].first] = i;
    id[a[i].second] = i;
  }
  sort(begin(evs), end(evs));
  ll tot = 0; int flag = 1;
  set<int> sl, sr;
  for (auto& e: evs) {
    if (e.second == 1) {
      sl.insert(e.first);
      sr.insert(ri[e.first]);
    } else if (e.second == -1) {
      auto it = sl.rbegin();
      vector<int> del;
      while (flag && it != sl.rend()) {
        if (*it <= le[e.first]) break;
        flag &= join(id[e.first], id[*it]);
        del.push_back(*it);
        it++;
      }
      sl.erase(le[e.first]);
      // for (auto& x: del) sl.erase(x);
    }
    if (!flag) break;
  }
  int c = 0;
  for (int i = 1; i <= n; i++) if (find(i) == i) c++;
  if (c > 1) flag = 0;
  if (flag) puts("YES");
  else puts("NO");
  return 0;
}