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
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, m, l, a[maxn], b[maxn], c[maxn];
int ap[maxn], bp[maxn];
int aq[maxn], bq[maxn];

int find(int n, int a[], int pos[]) {
  int j = 1;
  for (int i = 1; i <= l; i++) {
    while (j <= n && a[j] != c[i]) j++;
    if (j == n + 1) return -1;
    assert(a[j] == c[i]);
    pos[i] = j;
    j++;
  }
  return j;
}

int main() {
  while (scanf("%d%d%d", &n, &m, &l) == 3) {
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    for (int i = 1; i <= m; i++) {
      scanf("%d", b + i);
    }
    for (int i = 1; i <= l; i++) {
      scanf("%d", c + i);
    }
    ap[l + 1] = n + 1;
    bp[l + 1] = m + 1;
    int p1 = find(n, a, ap);
    int p2 = find(m, b, bp);
    if (p1 == -1 || p2 == -1) {
      puts("NO");
    } else {
      bool flag = false;
      reverse(a + 1, a + 1 + n);
      reverse(b + 1, b + 1 + m);
      reverse(c + 1, c + 1 + l);
      find(n, a, aq);
      find(m, b, bq);
      aq[l + 1] = n + 1;
      bq[l + 1] = m + 1;
      for (int i = 1; i <= l; i++) {
        aq[i] = n + 1 - aq[i];
        bq[i] = m + 1 - bq[i];
      }
      reverse(aq + 1, aq + 1 + l);
      reverse(bq + 1, bq + 1 + l);
      reverse(a + 1, a + 1 + n);
      reverse(b + 1, b + 1 + m);
      reverse(c + 1, c + 1 + l);
      // for (int i = 0; i <= l + 1; i++) {
      //   dbg(i, ap[i], aq[i]);
      // }
      for (int i = 0; i <= l && !flag; i++) {
        int st = ap[i] + 1;
        int ed = aq[i + 1] - 1;
        set<int> f;
        for (int i = st; i <= ed; i++) {
          f.insert(a[i]);
        }
        st = bp[i] + 1;
        ed = bq[i + 1] - 1;
        for (int i = st; i <= ed; i++) {
          if (f.count(b[i])) {
            flag = true;
            break;
          }
        }
      }
      puts(flag ? "NO" : "YES");
    }
  }
  return 0;
}