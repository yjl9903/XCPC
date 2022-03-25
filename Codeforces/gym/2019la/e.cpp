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

char s[maxn];
int n, k;

int main() {
  scanf("%s%d", s + 1, &k);
  n = strlen(s + 1);
  ll ans = 0; int last = -inf;
  for (int i = 1; i <= n; i++) {
    if (s[i] == 'E') last = i - n;
  }
  for (int i = 1; i <= n; i++) {
    if (s[i] == 'E') last = i;
    if (i - last + 1 <= k) {
      ans += k - (i - last + 1) + 1;
    }
  }
  cout << ans << endl;
  return 0;
}