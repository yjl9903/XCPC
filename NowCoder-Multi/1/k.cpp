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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, a[maxn];
double sq[maxn];

int main() {
  for (int i = 1; i < maxn; i++) sq[i] = sqrt(i);
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    auto cal = [&](int x, int y) { return sq[abs(x - y)]; };
    for (int _ = 0; _ < 5; _++) {
      for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
          double x1 = cal(i - 1, a[i]);
          double x2 = cal(j - 1, a[j]);
          double y1 = cal(i - 1, a[j]);
          double y2 = cal(j - 1, a[i]);
          if (x1 + x2 > y1 + y2) {
            swap(a[i], a[j]);
          }
        }
      }
    }
    for (int i = 1; i <= n; i++) printf("%d%c", a[i], " \n"[i == n]);
  }
  return 0;
}