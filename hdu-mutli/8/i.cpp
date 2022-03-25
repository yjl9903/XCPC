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
#include <ctime>
#include <random>
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
using ull = unsigned long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 5000000 + 5;
const int seed = 135;
const unsigned int mask32 = ~(0u);

mt19937 rnd(time(nullptr));

int n;
char s[maxn];

ull xp1[maxn], xp2[maxn], xp[maxn];

int p1 = 1e9 + 7, p2 = 1e9 + 9;
const vector<int> primes {
  1000000007, 1000000009,
  998244353, 91815541,
  122420729, 917120411,
  687840301, 515880193,
  1222827239, 1610612741
};

struct Hash {
  static void init() {
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
  ull build(int n, const char* s) {
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
    ull left1 = h[l - 1] >> 32, right1 = h[r] >> 32;
    ull left2 = h[l - 1] & mask32, right2 = h[r] & mask32;
    return (((right1 - left1 * xp1[len] % p1 + p1) % p1) << 32) |
            (((right2 - left2 * xp2[len] % p2 + p2) % p2));
  }

  static ull shift(ull x, int len) {
    ull a = x >> 32, b = x & mask32;
    a = (a * xp1[len]) % p1;
    b = (b * xp2[len]) % p2;
    return (a << 32) | b;
  }
  static ull add(ull x, ull y) {
    ull a1 = x >> 32, a2 = y >> 32;
    ull b1 = x & mask32, b2 = y & mask32;
    ull a = (a1 + a2) % p1;
    ull b = (b1 + b2) % p2;
    return (a << 32) | b;
  }
} h;

bool solve(int len) {
  if (len == n) return false;
  // dbg(len);
  vector<ull> all = { h.query(1, len) };
  for (int i = 1; i < len; i++) {
    ull a = h.query(1, i);
    ull b = h.query(i + 1, len);
    all.emplace_back(Hash::add(Hash::shift(b, i), a));
  }
  sort(begin(all), end(all));
  // for (auto& x: all) {
  //   dbg(x);
  // }
  auto gid = [&all](ull x) {
    auto it = lower_bound(begin(all), end(all), x);
    if (it != end(all)) {
      return *it == x;
    } else {
      return false;
    }
  };
  bool r = true;
  for (int i = len + 1; i + len - 1 <= n && r; i += len) {
    r &= gid(h.query(i, i + len - 1));
  }
  return r;
}

int main() {
  Hash::init();
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%s", &n, s + 1);
    h.build(n, s);
    bool flag = false;
    for (int i = 1; 1ll * i * i <= n && !flag; i++) {
      if (n % i) continue;
      flag |= solve(i);
      if (!flag && 1ll * i * i != n) {
        flag |= solve(n / i);
      }
    }
    puts(flag ? "Yes" : "No");
  }
  return 0;
}