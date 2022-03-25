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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, a[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  set<int> st = { 0, 1, 2, 4, 5 };
  auto check = [&](int x) -> bool {
    ll y = x + (ll)8e9 - 1;
    return st.count((int)(y % 8));
  };
  int ans = 0, last = 0;
  for (int i = 1; i <= n + 1; i++) {
    if (i == n + 1 || !check(a[i])) {
      ans = max(ans, i - 1 - last);
      last = i;
    }
  }
  cout << ans;
  return 0;
}