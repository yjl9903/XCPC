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

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    bool flag = true;
    string prefix, suffix, ind;
    for (int i = 1; i <= n; i++) {
      scanf("%s", s);
      int m = strlen(s), fi = -1, se = -1;
      for (int i = 0; i < m; i++) {
        if (s[i] == '*') {
          fi = i; break;
        }
        if (i < (int)prefix.length()) {
          if (s[i] != prefix[i]) {
            flag = false;
          }
        } else {
          prefix += s[i];
        }
      }
      reverse(s, s + m);
      for (int i = 0; i < m; i++) {
        if (s[i] == '*') {
          se = m - i - 1; break;
        }
        if (i < (int)suffix.length()) {
          if (s[i] != suffix[i]) {
            flag = false;
          }
        } else {
          suffix += s[i];
        }
      }
      reverse(s, s + m);
      for (int i = fi; i <= se; i++) {
        if (s[i] != '*') {
          ind += s[i];
        }
      }
    }
    printf("Case #%d: ", ++kase);
    if (flag) {
      reverse(begin(suffix), end(suffix));
      string ans = prefix + ind + suffix;
      printf("%s\n", ans.c_str());
    } else {
      puts("*");
    }
  }
  return 0;
}