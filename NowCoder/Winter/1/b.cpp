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
const int maxn = 100000 + 5;

int n, x, a, b;

int main() {
  cin >> n >> x >> a >> b;
  double s = x * a / 100.0 + (100 - x) * b / 100.0;
  printf("%.2lf\n", s * n);
  return 0;
}