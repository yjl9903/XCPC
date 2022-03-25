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

ll lcm(ll a, ll b) {
  return a * b / __gcd(a, b);
}

bool check(ll x) {
  ll n = x;
  while (x) {
    ll a = x % 10;
    if (a && n % a) {
      return false;
    }
    x /= 10;
  }
  return true;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    ll n;
    scanf("%lld", &n);
    while (!check(n)) {
      n++;
    }
    printf("%lld\n", n);
  }
  return 0;
}