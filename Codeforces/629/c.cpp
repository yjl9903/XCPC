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
char s[maxn], a[maxn], b[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%s", &n, s + 1);
    a[1] = b[1] = '1';
    bool flag = false;
    for (int i = 2; i <= n; i++) {
      if (s[i] == '0') {
        a[i] = b[i] = '0';
      } else if (s[i] == '1') {
        if (flag) {
          a[i] = '0'; b[i] = '1';
        } else {
          a[i] = '1'; b[i] = '0';
          flag = true;
        }
      } else if (s[i] == '2') {
        if (flag) {
          a[i] = '0'; b[i] = '2';
        } else {
          a[i] = b[i] = '1';
        }
      }
    }
    a[n + 1] = b[n + 1] = 0;
    printf("%s\n%s\n", a + 1, b + 1);
  }
  return 0;
}