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

int n;
char s[maxn];
const char pat[] = "110";

ll cal(int st) {
  int cur = 1;
  for (int i = 1; i <= n; i++) {
    if (i != 1) {
      if (st == 0) {
        cur++;
      }
    }
    if (s[i] != pat[st]) {
      return 0ll;
    }
    if (st == 2) {
      st = 0;
    } else {
      st++;
    }
  }
  return 10000000000 - cur + 1;
}

int main() {
  scanf("%d%s", &n, s + 1);
  if (n == 1) {
    if (s[1] == '1') {
      puts("20000000000");
    } else {
      puts("10000000000");
    }
  } else if (n == 2) {
    if (s[1] == '1') {
      puts("10000000000");
    } else {
      if (s[2] == '0') {
        puts("0");
      } else {
        puts("9999999999");
      }
    }
  } else {
    ll ans = cal(0);
    ans = max(ans, cal(1));
    ans = max(ans, cal(2));
    printf("%lld\n", ans);
  }
  return 0;
}