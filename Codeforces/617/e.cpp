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

int n, dp[26], ans[maxn];
char s[maxn];

int main() {
  scanf("%d%s", &n, s + 1);
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    int mx = 0;
    for (int j = s[i] - 'a' + 1; j < 26; j++) {
      mx = max(mx, dp[j]);
    }
    dp[s[i] - 'a'] = mx + 1;
    ans[i] = mx + 1;
    cnt = max(mx + 1, cnt);
  }
  printf("%d\n", cnt);
  for (int i = 1; i <= n; i++) {
    printf("%d ", ans[i]);
  }
  return 0;
}