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

int n, a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    vector<int> stk = { a[1] };
    for (int i = 2; i <= n; i++) {
      while (stk.size() > 1 && stk.back() < a[i]) {
        stk.pop_back();
      }
      if (stk.size() == 1) {
        if (a[i] < stk.back()) {
          stk.push_back(a[i]);
        }
      } else {
        stk.push_back(a[i]);
      }
    }
    puts(stk.size() <= 1 ? "YES" : "NO");
  }  
  return 0;
}