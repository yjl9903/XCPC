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

ll k;

ll pow(ll x, int n = 10) {
  ll r = 1;
  for (int i = 0; i < n; i++) {
    r *= x;
  }
  return r;
}

char cf[] = "codeforces";

int main() {
  scanf("%I64d", &k);
  int mx = 1;
  for (int i = 1; i < 58; i++) {
    if (pow(i, 10) < k) {
      mx = i;
    } else {
      break;
    }
  }
  vector<int> vec(10, mx);
  ll tot = pow(mx, 10);
  for (int i = 0; i < 10 && tot < k; i++) {
    tot /= mx; tot *= mx + 1;
    vec[i]++;
  }
  assert(tot >= k);
  for (int i = 0; i < 10; i++) {
    int x = vec[i];
    while (x--) putchar(cf[i]);
  }
  return 0;
}