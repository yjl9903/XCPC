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
const double pi = acos(-1.0);

int n, p[16];
double R[16];
PII a[16];

double dis(PII a, PII b) {
  int x = a.first - b.first;
  int y = a.second - b.second;
  return hypot(x, y);
}

int main() {
  int x1, x2, y1, y2;
  cin >> n >> x1 >> y1 >> x2 >> y2;
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &a[i].first, &a[i].second);
    p[i] = i;
  }
  double ans = 0;
  do {
    double sum = 0;
    for (int i = 0; i < n; i++) {
      int x = a[p[i]].first;
      int y = a[p[i]].second;
      R[i] = min(abs(x1 - x), abs(x2 - x));
      R[i] = min(R[i], 1.0 * abs(y1 - y));
      R[i] = min(R[i], 1.0 * abs(y2 - y));
      // for (int j = 0; j < n; j++) {
      //   if (i == j) continue;
      //   R[i] = min(R[i], dis(a[p[i]], a[p[j]]));
      // }
      for (int j = 0; j < i; j++) {
        double d = dis(a[p[i]], a[p[j]]);
        R[i] = min(R[i], d - R[j]);
      }
      R[i] = max(R[i], 0.0);
      sum += 1.0 * pi * R[i] * R[i];
    }
    ans = max(ans, sum);
  } while (next_permutation(p, p + n));
  printf("%.0lf\n", abs(x1 - x2) * abs(y1 - y2) - ans);
  return 0;
}