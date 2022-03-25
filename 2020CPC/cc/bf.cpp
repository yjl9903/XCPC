#include <bits/stdc++.h>
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
using namespace std;
using ll = long long;
const int mod = 1e9 + 7;
const int maxn = 500000 + 5;

int add(int x, int y) {
  x += y;
  return x >= mod ? x - mod : x;
}
int sub(int x, int y) {
  x -= y;
  return x >= 0 ? x : x + mod;
}
int mul(int x, int y) { return 1ll * x * y % mod; }
int qpow(int a, int n = mod - 2) {
  int r = 1;
  while (n) {
    if (n & 1) r = 1ll * r * a % mod;
    a = 1ll * a * a % mod;
    n >>= 1;
  }
  return r;
}

char s[maxn];
int n, sum, p[30], pre[maxn], suf[maxn], sufM[maxn];

char t[maxn];
int fail[maxn], f[maxn];

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  for (int i = 0; i < 26; i++) {
    scanf("%d", p + i);
    sum += p[i];
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int m = 0;
    f[0] = 1;
    for (int j = i; j <= n; j++) {
      t[++m] = s[j];
      f[m] = mul(f[m - 1], mul(qpow(p[s[j] - 'a']), sum));
    }
    fail[1] = 0;
    ans = add(ans, f[1]);
    for (int i = 2; i <= m; i++) {
      int cur = fail[i - 1];
      while (cur && t[cur + 1] != t[i]) cur = fail[cur];
      if (t[cur + 1] == t[i]) cur++;
      fail[i] = cur;
      cur = i;
      while (cur) {
        ans = add(ans, f[cur]);
        cur = fail[cur];
      }
    }
  }
  cout << ans << endl;
  return 0;
}