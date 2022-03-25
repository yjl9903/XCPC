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

map<ll,bool> ans;

bool cal(ll n) {
  if (n == 1) return 0;
  if (ans.count(n)) return ans[n];
  return ans[n] = (!cal(n / 2) + !cal(n - n / 2));
}

string show(int x) {
  string ans;
  while (x) {
    ans += x % 2 + '0';
    x /= 2;
  }
  // reverse(begin(ans), end(ans));
  int last = -1;
  string tot;
  for (int i = 0; i < (int)ans.size(); i++) {
    if (ans[i] == '1') {
      tot += i - last + '0';
      last = i;
    }
  }
  return tot;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    if (cal(i)) {
      printf("%d %s\n", i, show(i).c_str());
    }
    // printf("%s %d\n", show(i).c_str(), cal(i));
  }
  // int T; scanf("%d", &T);
  // while (T--) {
  //   ll n;
  //   scanf("%lld", &n);
  //   puts(cal(n) ? "XiaoHuiHui" : "XiaoQiao");
  // }
  return 0;
}