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
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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
const int maxn = 100 + 5;

int add(int x, int y) {
  x += y; return x >= mod ? x - mod : x;
}
int mul(int x, int y) {
  return 1ll * x * y % mod;
}
int lcm(int a, int b) {
  return a / __gcd(a, b) * b;
}

int n, C[maxn][maxn], fac[maxn]; 
ll k;
map<int,int> dp[maxn];

int main() {
  int S = 50;
  fac[0] = 1;
  for (int i = 1; i <= S; i++) {
    fac[i] = mul(i, fac[i - 1]);
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; j++) {
      C[i][j] = add(C[i - 1][j], C[i - 1][j - 1]);
    }
  }
  dp[0][1] = 1;
  for (int i = 1; i <= S; i++) {
    dp[i] = dp[i - 1];
    for (int j = 2; j <= i; j++) {
      for (auto& x: dp[i - j]) {
        int sum = mul(mul(x.second, C[i - 1][j - 1]), fac[j - 1]);
        dp[i][lcm(x.first, j)] = add(dp[i][lcm(x.first, j)], sum);
      }
    }
  }
  ios::sync_with_stdio(false);
  int T; cin >> T;
  while (T--) {
    cin >> n >> k;
    int ans = 0;
    for (auto& x: dp[n]) {
      // dbg(x.first, x.second);
      if (k % x.first == 0) {
        ans = add(ans, x.second);
      }
    }
    cout << ans << '\n';
  }
  return 0;
}