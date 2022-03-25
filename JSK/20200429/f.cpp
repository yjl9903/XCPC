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

int n;
pair<double,double> a[maxn];

double cal(int i, int j) {
  return fabs(a[i].second - a[j].second) / fabs(a[i].first - a[j].first);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lf%lf", &a[i].first, &a[i].second);
  }
  sort(a + 1, a + 1 + n);
  double ans = cal(1, 2);
  for (int i = 3; i <= n; i++) {
    ans = max(ans, cal(i, i - 1));
  }
  printf("%.5lf\n", ans);
  return 0;
}