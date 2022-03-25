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

ll L, R;

ll solve(ll n) {
  ll ans = 0;
  for(ll l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    ans += (r - l + 1) * (n / l);
  }
  return ans;
}

int main() {
  cin >> L >> R;
  cout << solve(R) - solve(L - 1) << endl;
  return 0;
}