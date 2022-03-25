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

string day[5] = {
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday"
};

char buf[16];

int gday(string s) {
  for (int i = 0; i < 5; i++) {
    if (s == day[i]) return i;
  }
  assert(false);
}

ll get(int y, int m, int d) {
  ll ans = 1ll * (y - 1) * 12 * 30;
  ans += 1ll * (m - 1) * 30;
  ans += d;
  return ans;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    int y1, m1, d1;
    int y2, m2, d2;
    scanf("%d%d%d%s", &y1, &m1, &d1, buf);
    scanf("%d%d%d", &y2, &m2, &d2);
    ll v1 = get(y1, m1, d1);
    ll v2 = get(y2, m2, d2);
    int d = (v2 - v1) % 5;
    if (d == 0) {
      puts(buf);
    } else if (d > 0) {
      int ans = (gday(buf) + d) % 5;
      printf("%s\n", day[ans].c_str());
    } else if (d < 0) {
      int ans = (gday(buf) + d + 5) % 5;
      printf("%s\n", day[ans].c_str());
    }
  }
  return 0;
}