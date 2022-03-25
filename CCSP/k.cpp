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

char s[maxn];
int n, k;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s%d", s + 1, &k);
    n = strlen(s + 1);
    string ans;
    int last = 1;
    for (int i = n - k - 1; i >= 0; i--) {
      char mx = 'z' + 1; int pos = -1;
      for (int j = last; j <= n - i; j++) {
        if (s[j] < mx) {
          pos = j; mx = s[j];
        }
      }
      assert(pos != -1);
      last = pos + 1;
      ans += mx;
    }
    printf("%s\n", ans.c_str());
  }
  return 0;
}