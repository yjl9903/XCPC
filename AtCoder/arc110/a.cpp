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

ll lcm(ll x, ll y) {
  return x / __gcd(x, y) * y;
}

int n;

int main() {
  cin >> n;
  ll g = 1;
  for (int i = 2; i <= n; i++) {
    g = lcm(g, i);
  }
  printf("%lld\n", g + 1);
  return 0;
}