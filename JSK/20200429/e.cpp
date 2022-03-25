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

int main() {
  scanf("%d", &n);
  double ans = 1.0, tot = 1.0;
  for (int i = 1; i <= n; i++) {
    tot /= i;
    ans += tot;
  }
  printf("%.12lf\n", ans);
  return 0;
}