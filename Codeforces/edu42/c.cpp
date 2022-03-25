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

char s[maxn];

int main() {
  scanf("%s", s);
  int n = strlen(s), ans = -1;
  for (int i = 1; i < (1 << n); i++) {
    int r = 0, c = 0;
    for (int j = 0; j < 10; j++) {
      if (i >> j & 1) {
        if (!r && s[j] == '0') break;
        r = r * 10 + s[j] - '0';
        c++;
      }
    }
    if (!c) continue;
    int x = sqrt(r);
    if (1ll * x * x == r) {
      ans = max(ans, c);
    }
  }
  if (ans == -1) {
    puts("-1");
  } else {
    printf("%d\n", n - ans);
  }
  return 0;
}