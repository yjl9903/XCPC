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

int n;

int main() {
  scanf("%d", &n);
  ll ans = 0;
  for (int i = 1; 1ll * i * i <= n; i++) {
    int x = i * i;
    for (int j = 1; 1ll * j * j <= x; j++) {
      if (x % j) continue;
      ans++;
      if (x != j * j) ans++;
    }
  }
  cout << ans;
  return 0;
}