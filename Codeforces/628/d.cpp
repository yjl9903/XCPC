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

ll x, s;

int main() {
  cin >> x >> s;
  if (x > s) return puts("-1"), 0;
  if (x == s && x == 0) return puts("0"), 0;
  if (x == s) {
    puts("1");
    printf("%I64d\n", x);
    return 0;
  }
  if ((s - x) % 2 == 0) {
    ll a = (s - x) / 2;
    if ((a + x) == (a ^ x)) {
      puts("2");
      printf("%I64d %I64d\n", a, x ^ a);
    } else {
      puts("3");
      printf("%I64d %I64d %I64d\n", a, a, x);
    }
  } else {
    puts("-1");
  }
  return 0;
}