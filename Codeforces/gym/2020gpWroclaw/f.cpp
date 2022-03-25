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

int n;
char buf[4], s[maxn], t[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%s%s%s", &n, buf, s + 1, t + 1);
    char ch = buf[0];
    bool ok = false;
    for (int T = 0; T < 26; T++) {
      int g = 0;
      if (s[n] == 'z') s[n] = 'a', g = 1;
      else s[n]++;
      bool flag = s[n] == t[n];
      for (int i = n - 1; i >= 1; i--) {
        if (g > 0) {
          if (s[i] == 'z') {
            s[i] = 'a';
            g = 1;
          } else {
            s[i]++;
            g = 0;
          }
        }
        if (s[i] != t[i]) {
          flag = false;
        }
      }
      assert(g == 0);
      if (!flag) {
        bool ans = false;
        for (int i = 1; i <= n; i++) {
          if (s[i] == buf[0]) {
            ans = true;
            break;
          }
        }
        if (ans) {
          puts(s + 1);
          ok = true;
          break;
        }
      } else {
        break;
      }
    }
    if (!ok) {
      puts("NO");
    }
  }
  return 0;
}