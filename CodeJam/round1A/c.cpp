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
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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

int n, m, a[maxn], b[maxn];
int preR[maxn], sufR[maxn], preC[maxn], sufC[maxn];

int get(int x, int y) {
  return x * m + y;
}

void update() {
  for (int i = 0; i < n; i++) {
    int last = 0;
    for (int j = 0; j < m; j++) {
      if (a[get(i, j)] > 0) {
        preR[get(i, j)] = a[get(i, j)];
        last = a[get(i, j)];
      } else {
        preR[get(i, j)] = last;
      }
    }
    last = 0;
    for (int j = m - 1; j >= 0; j--) {
      if (a[get(i, j)] > 0) {
        sufR[get(i, j)] = a[get(i, j)];
        last = a[get(i, j)];
      } else {
        sufR[get(i, j)] = last;
      }
    }
  }
  for (int j = 0; j < m; j++) {
    int last = 0;
    for (int i = 0; i < n; i++) {
      if (a[get(i, j)] > 0) {
        preC[get(i, j)] = a[get(i, j)];
        last = a[get(i, j)];
      } else {
        preC[get(i, j)] = last;
      }
    }
    last = 0;
    for (int i = n - 1; i >= 0; i--) {
      if (a[get(i, j)] > 0) {
        sufC[get(i, j)] = a[get(i, j)];
        last = a[get(i, j)];
      } else {
        sufC[get(i, j)] = last;
      }
    }
  }
}

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        scanf("%d", &a[get(i, j)]);
      }
    }
    update();
    ll ans = 0;
    while (true) {
      bool flag = false;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          if (a[get(i, j)] == 0) {
            b[get(i, j)] = 0;
            continue;
          }
          ans += a[get(i, j)];
          int p = i - 1, sum = 0, cnt = 0;
          if (i > 0 && preC[get(i - 1, j)] > 0) {
            cnt++; sum += preC[get(i - 1, j)];
          }
          if (i + 1 < n && sufC[get(i + 1, j)] > 0) {
            cnt++; sum += sufC[get(i + 1, j)];
          }
          if (j > 0 && preR[get(i, j - 1)] > 0) {
            cnt++; sum += preR[get(i, j - 1)];
          }
          if (j + 1 < m && sufR[get(i, j + 1)] > 0) {
            cnt++; sum += sufR[get(i, j + 1)];
          }
          if (cnt > 0 && cnt * a[get(i, j)] < sum) {
            b[get(i, j)] = 0;
            flag = true;
          } else {
            b[get(i, j)] = a[get(i, j)];
          }
        }
      }
      swap(a, b);
      if (!flag) break;
      update();
    }
    printf("Case #%d: %lld\n", ++kase, ans);
  }
  return 0;
}