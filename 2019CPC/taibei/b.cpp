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

int main() {
  int x; vector<int> v;
  while (cin >> x) v.push_back(x);
  reverse(begin(v), end(v));
  for (int x: v) {
    double ans = sqrt(abs(x)) + 1ll * x * x * x * 5;
    if (ans < 400) {
      printf("f(%d) = %.2lf\n", x, ans);
    } else {
      printf("f(%d) = MAGNA NIMIS!\n", x);
    }
  }
  return 0;
}