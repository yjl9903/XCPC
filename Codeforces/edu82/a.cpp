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
int n;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    int fi = -1, la = -1;
    for (int i = 1; i <= n; i++) {
      if (s[i] == '1') {
        fi = i; break;
      }
    }
    for (int i = n; i >= 1; i--) {
      if (s[i] == '1') {
        la = i; break;
      }
    }
    if (fi == -1) {
      puts("0");
    } else {
      int ans = 0;
      for (int i = fi; i <= la; i++) {
        if (s[i] == '0') {
          ans++;
        }
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}