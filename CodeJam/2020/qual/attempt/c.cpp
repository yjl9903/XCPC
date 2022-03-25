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
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 24 * 60;
const int maxn = 200000 + 5;

struct Line {
  int l, r, id;
} a[maxn];

int n;

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", &a[i].l, &a[i].r);
      a[i].id = i;
    }
    sort(a + 1, a + 1 + n, [](Line a, Line b) {
      if (a.r == b.r) return a.l < b.l;
      return a.r < b.r;
    });
    vector<int> used = { 1 };
    set<int> vis = { 1 };
    for (int i = 2; i <= n; i++) {
      for (int j = used.back() + 1; j <= n; j++) {
        if (vis.count(j)) continue;
        if (a[j].l >= a[used.back()].r) {
          used.push_back(j);
          vis.insert(j);
          break;
        }
      }
    }
    int flag = true;
    string ans(n, ' ');
    vector<Line> vecb;
    for (int i = 1, p = 0; i <= n; i++) {
      if (p < (int)used.size() && used[p] == i) {
        ans[a[i].id - 1] = 'J';
        p++;
      } else {
        ans[a[i].id - 1] = 'C';
        vecb.push_back(a[i]);
      }
    }
    sort(begin(vecb), end(vecb), [](Line a, Line b) {
      return a.l < b.l;
    });
    for (int i = 1; i < (int)vecb.size(); i++) {
      if (vecb[i].l < vecb[i - 1].r) {
        flag = false; break;
      }
    }
    printf("Case #%d: ", ++kase);
    if (flag) {
      puts(ans.c_str());
    } else {
      puts("IMPOSSIBLE");
    }
  }
  return 0;
}