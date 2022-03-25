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
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

char pat[] = "NowCoder";
char s[maxn];
int n;

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  vector<int> R;
  for (int i = 8; i <= n; i++) {
    bool flag = true;
    for (int j = i - 7, k = 0; j <= i; j++, k++) {
      flag &= s[j] == pat[k];
    }
    if (flag) {
      R.push_back(i);
    }
  }
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    int pos = lower_bound(R.begin(), R.end(), i + 7) - R.begin();
    if (pos < R.size()) {
      ans += n - R[pos] + 1;
    }
  }
  cout << ans << endl;
  return 0;
}