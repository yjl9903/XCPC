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
const int base = 131;
const int mod = 19681001;
const int maxn = 1000000 + 5;

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

int n, xp[maxn], vis[maxn];
char s[maxn];

int main() {
  xp[0] = 1;
  for (int i = 1; i < maxn; i++) {
    xp[i] = mul(xp[i - 1], base);
  }
  scanf("%d", &n);
  vector<string> allS;
  for (int i = 1; i <= n; i++) {
    scanf("%s", s + 1);
    int m = strlen(s + 1);
    allS.push_back(s + 1);
    for (int j = 1; j <= m; j++) {
      if (s[j] == '1') {
        vis[j] ^= 1;
      }
    }
  }
  int val = 0;
  for (int j = 1; j < maxn; j++) {
    if (vis[j]) {
      val = add(val, xp[j]);
    }
  }
  int ans = 0;
  for (string& str: allS) {
    int cur = 0;
    for (int j = str.length(); j > 1; j--) {
      cur = mul(cur, base);
      if (str[j - 1] == '1') {
        vis[j] ^= 1;
        if (vis[j]) {
          val = add(val, xp[j]);
        } else {
          val = sub(val, xp[j]);
        }
        cur = add(cur, base);
      }
      if (cur == val) {
        ans++;
      }
    }
    for (int j = str.length(); j > 1; j--) {
      if (str[j - 1] == '1') {
        vis[j] ^= 1;
        if (vis[j]) {
          val = add(val, xp[j]);
        } else {
          val = sub(val, xp[j]);
        }
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}