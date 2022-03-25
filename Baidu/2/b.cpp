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

int n, suf[maxn];
char s[maxn], t[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%s%s", &n, s + 1, t + 1);
    suf[n + 1] = suf[n + 2] = 0;
    s[n + 1] = '0';
    t[n + 1] = '0';
    for (int i = n; i >= 1; i--) {
      suf[i] = suf[i + 1] + (s[i] != t[i]);
    }
    int ans = suf[1];
    int zero = s[1] == '0';
    int pre = t[1] == '1';
    for (int i = 2; i <= n + 1; i++) {
      int cost = 1 + (s[i] == '1') + zero;
      cost += pre + (t[i] == '0');
      ans = min(ans, cost + suf[i + 1]);

      zero += s[i] == '0';
      pre += t[i] == '1';
    }
    printf("%d\n", ans);
  } 
  return 0;
}