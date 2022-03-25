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
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    ll x = n + 1, y = 1ll * n * (n + 1);
    printf("%lld\n", x ^ y);
  }
  return 0;
}