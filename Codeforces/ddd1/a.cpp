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
const int maxn = 100000 + 5;

char s[maxn];
int n, suf[maxn];

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  for (int i = n; i >= 1; i--) {
    suf[i] = suf[i + 1];
    if (s[i] == 'Q') suf[i]++;
  }
  int sum = 0;
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    if (s[i] == 'A') {
      ans += 1ll * sum * suf[i + 1];
    }
    if (s[i] == 'Q') sum++;
  }
  cout << ans;
  return 0;
}