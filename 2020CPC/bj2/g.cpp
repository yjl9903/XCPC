#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <random>
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
const int maxn = 400000 + 5;

typedef unsigned long long ull;
const int seed = maxn;
int p1 = 1e9 + 7, p2 = 1e9 + 9;
ull xp1[maxn], xp2[maxn], xp[maxn];
vector<int> primes {
  1000000007, 1000000009,
  998244353, 91815541,
  122420729, 917120411,
  687840301, 515880193,
  1222827239, 1610612741
};

struct Hash {
  static void init() {
    mt19937 rnd(time(nullptr));
    p1 = primes[rnd() % primes.size()];
    p2 = primes[rnd() % primes.size()];
    while (p1 == p2) {
      p2 = primes[rnd() % primes.size()];
    }
    xp1[0] = xp2[0] = xp[0] = 1;
    for (int i = 1; i < maxn; ++i) {
      xp1[i] = xp1[i - 1] * seed % p1;
      xp2[i] = xp2[i - 1] * seed % p2;
      xp[i] = xp[i - 1] * seed;
    }
  }

  ull h[maxn];
  ull build(int n, const int* s) {
    ull r1 = 0, r2 = 0;
    for (int i = 1; i <= n; i++) {
      r1 = (r1 * seed + s[i]) % p1;
      r2 = (r2 * seed + s[i]) % p2;
      h[i] = (r1 << 32) | r2;
    }
    return h[n];
  }

  ull query(int l, int r) {
      int len = r - l + 1;
      unsigned int mask32 = ~(0u);
      ull left1 = h[l - 1] >> 32, right1 = h[r] >> 32;
      ull left2 = h[l - 1] & mask32, right2 = h[r] & mask32;
      return (((right1 - left1 * xp1[len] % p1 + p1) % p1) << 32) |
              (((right2 - left2 * xp2[len] % p2 + p2) % p2));
  }
} h1, h2;

int n, a[maxn], b[maxn];

int main() {
  Hash::init();
  while (scanf("%d", &n) == 1) {
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      b[n - i + 1] = a[i];
    }
    for (int i = 1; i <= n; i++) {
      a[i + n] = a[i];
      b[i + n] = b[i];
    }
    h1.build(n + n, a);
    h2.build(n + n, b);
    set<ull> st;
    for (int i = 1; i <= n; i++) {
      auto x = h1.query(i, i + n - 1);
      auto y = h2.query(i, i + n - 1);
      st.insert(x);
      st.insert(y);
    }
    printf("%d\n", st.size());
  }
  return 0;
}