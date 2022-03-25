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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200 + 5;

inline int add(int x, int y) {
  x += y;
  return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
  x -= y;
  return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
  return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
  int r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x % mod;
    n >>= 1; x = 1ll * x * x % mod;
  }
  return r;
}
inline int inv(int x) {
  return qpow(x, mod - 2);
}
inline int C(int n, int m) {
  int ans = 1;
  for (int i = 0; i < m; i++) {
    ans = mul(ans, n - i);
    ans = mul(ans, inv(m - i));
  }
  return ans;
}

int n, dp[maxn][maxn];
PII a[maxn];

int main() {
  scanf("%d", &n);
  int iv = 1;
  vector<int> lsh;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].first, &a[i].second);
    a[i].second++;
    lsh.push_back(a[i].first);
    lsh.push_back(a[i].second);
    iv = mul(iv, inv(a[i].second - a[i].first));
  }
  sort(begin(lsh), end(lsh));
  lsh.resize(unique(begin(lsh), end(lsh)) - begin(lsh));
  int nn = lsh.size();
  auto gid = [&lsh](int x) {
    return lower_bound(begin(lsh), end(lsh), x) - begin(lsh) + 1;
  };
  for (int i = 0; i <= nn; i++) dp[0][i] = 1;
  for (int i = 1; i <= n; i++) {
    a[i].first = gid(a[i].first);
    a[i].second = gid(a[i].second);
    for (int j = a[i].first; j < a[i].second; j++) {
      for (int k = i; k >= 1; k--) {
        if (j < a[k].first || j >= a[k].second) break;
        int dx = lsh[j] - lsh[j - 1];
        int dy = i - k + 1;
        dp[i][j] = add(dp[i][j], mul(C(dx + dy - 1, dy), dp[k - 1][j + 1]));
      }
    }
    for (int j = nn; j >= 1; j--) {
      dp[i][j] = add(dp[i][j], dp[i][j + 1]);
    }
  }
  cout << mul(dp[n][1], iv) << endl;
  return 0;
}