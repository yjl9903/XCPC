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

int a, b, c;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &a, &b, &c);
    if (b == 0) {
      if (a) {
        for (int i = 0; i <= a; i++) putchar('0');
      } else if (c) {
        for (int i = 0; i <= c; i++) putchar('1');
      } else {
        assert(false);
      }
      puts("");
      continue;
    }
    string ans;
    for (int i = 0; i <= b; i++) {
      ans += i % 2 + '0';
    }
    for (int i = 0; i < a; i++) {
      ans = '0' + ans;
    }
    int pos = ans.find('1');
    for (int i = 0; i < c; i++) {
      ans.insert(begin(ans) + pos, '1');
    }
    puts(ans.c_str());
  }
  return 0;
}