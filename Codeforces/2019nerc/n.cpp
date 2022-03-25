#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <map>
#include <functional>
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
const int maxn = 100000 + 5;

int n, pre[maxn * 2], isring[maxn], deg[maxn * 2];
PII e[maxn];

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
int join(int x, int y) {
  x = find(x); y = find(y);
  if (x == y) return 1;
  pre[x] = y;
  return 0;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    vector<int> lsh;
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", &e[i].first, &e[i].second);
      lsh.push_back(e[i].first);
      lsh.push_back(e[i].second);
      isring[i] = 0;
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    int nn = (int)lsh.size();
    for (int i = 1; i <= nn; i++) pre[i] = i, deg[i] = 0;
    auto gid = [&](int x) -> int {
      return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
    };
    for (int i = 1; i <= n; i++) {
      e[i].first = gid(e[i].first);
      e[i].second = gid(e[i].second);
      deg[e[i].first]++;
      deg[e[i].second]++;
      isring[i] = join(e[i].first, e[i].second);
    }
    int first = -1;
    // for (int i = 1; i <= nn; i++) {
    //   if (i != pre[i]) continue;
    //   if (first == -1) {
    //     first = i; continue;
    //   }
    // }
    vector< tuple<int,int,int> > ans;
    for (int i = 1; i <= n; i++) {
      if (first == -1) {
        first = find(e[i].first);
      } else if (find(e[i].first) != find(first)) {
        if (isring[i]) {
          join(e[i].first, first);
          ans.emplace_back(i, e[i].first, first);
        } else {
          if (deg[e[i].first] == 1) {
            join(e[i].first, first);
            ans.emplace_back(i, e[i].first, first);
          } else if (deg[e[i].second] == 1) {
            join(e[i].second, first);
            ans.emplace_back(i, e[i].second, first);
          }
        }
      }
    }
    printf("%d\n", (int)ans.size());
    for (auto x: ans) {
      int w, a, b;
      tie(w, a, b) = x;
      printf("%d %d %d\n", w, lsh[a - 1], lsh[b - 1]);
    }
  }
  return 0;
}