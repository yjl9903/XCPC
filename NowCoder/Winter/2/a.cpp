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

int a[3], b[3];

int main() {
  for (int i = 0; i < 3; i++) scanf("%d", a + i);
  for (int i = 0; i < 3; i++) scanf("%d", b + i);
  ll ans = 1ll * min(a[0], b[1]) + 1ll * min(a[1], b[2]) + 1ll * min(a[2], b[0]);
  cout << ans;
  return 0;
}