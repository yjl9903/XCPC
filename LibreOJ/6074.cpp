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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

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

const int Size = 9;

int n, q, A[10][10], B[10][10], S[maxn][10], D[maxn][10];
char s[maxn];

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  for (int j = 0; j <= Size; j++) {
    A[j][j] = B[j][j] = 1;
    S[0][j] = 1;
  }
  for (int i = 1; i <= n; i++) {
    int c = s[i] - 'a';
    for (int j = 0; j <= Size; j++) {
      S[i][j] = sub(mul(2, S[i - 1][j]), A[c][j]);
      A[c][j] = S[i - 1][j];
      D[i][j] = B[c][j];
      B[c][j] = sub(mul(2, B[c][j]), D[i - 1][j]);
    }
  }
  scanf("%d", &q);
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    int ans = mul(S[r][Size], sub(1, D[l - 1][Size]));
    for (int j = 0; j < Size; j++) {
      ans = sub(ans, mul(S[r][j], D[l - 1][j]));
    }
    printf("%d\n", sub(ans, 1));
  }
  return 0;
}