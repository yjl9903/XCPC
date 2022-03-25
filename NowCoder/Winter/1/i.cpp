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
const int maxn = 300000 + 5;

int n, a, b, c;
char s[maxn];
ll dp[maxn];

int nico(int r) {
  if (r < 4) return false;
  const char t[] = "nico";
  for (int i = r - 3, j = 0; i <= r; i++, j++) {
    if (s[i] != t[j]) {
      return false;
    }
  }
  return true;
}
int niconi(int r) {
  if (r < 6) return false;
  const char t[] = "niconi";
  for (int i = r - 5, j = 0; i <= r; i++, j++) {
    if (s[i] != t[j]) {
      return false;
    }
  }
  return true;
}
int niconiconi(int r) {
  if (r < 10) return false;
  const char t[] = "niconiconi";
  for (int i = r - 9, j = 0; i <= r; i++, j++) {
    if (s[i] != t[j]) {
      return false;
    }
  }
  return true;
}

int main() {
  scanf("%d%d%d%d%s", &n, &a, &b, &c, s + 1);
  for (int i = 1; i <= n; i++) {
    dp[i] = dp[i - 1];
    if (nico(i)) {
      dp[i] = max(dp[i], dp[i - 4] + a);
    }
    if (niconi(i)) {
      dp[i] = max(dp[i], dp[i - 6] + b);
    }
    if (niconiconi(i)) {
      dp[i] = max(dp[i], dp[i - 10] + c);
    }
  }
  printf("%lld\n", dp[n]);
  return 0;
}