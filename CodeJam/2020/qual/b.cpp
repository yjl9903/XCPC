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
int n;

string solve(int base, int l, int r) {
  string ans;
  for (int i = l, j; i <= r; i = j) {
    if (s[i] - '0' <= base) {
      ans += s[i];
      j = i + 1;
    } else {
      j = i;
      ans += "(";
      while (j <= r && s[j] - '0' > base) j++;
      ans += solve(base + 1, i, j - 1);
      ans += ")";
    }
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    auto ans = solve(0, 1, n);
    printf("Case #%d: %s\n", ++kase, ans.c_str());
    // for (int i = 0, j = 0; i < n; i = j) {
    //   if (s[i] == '0') {
    //     ans += '0'; j = i + 1;
    //   } else {
    //     ans += '(';
    //     j = i;
    //     while (j < n && s[j] == '1') ans += '1', j++;
    //     ans += ')';
    //   }
    // }
  }
  return 0;
}