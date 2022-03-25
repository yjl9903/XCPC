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
const int mod = 1e9 + 7;;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n;
ll suf[maxn], cnt[maxn];
char s[maxn];

int main() {
  scanf("%d%s", &n, s + 1);
  for (int i = n; i >= 1; i--) {
    suf[i] = suf[i + 1];
    cnt[i] = cnt[i + 1];
    if (s[i] == '1') {
      suf[i] += i;
      cnt[i]++;
    }
  }
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    if (s[i] == '1') {
      ans += suf[i + 1] - cnt[i + 1] * i;
    }
  }
  cout << ans % mod;
  return 0;
}