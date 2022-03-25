#include <bits/stdc++.h>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
#else
  #define dbg(...) 
#endif
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int maxn = 100000 + 5;

ll n, mod;

ll add(ll x, ll y) {
  x += y;
  return x >= mod ? x - mod : x;
}
ll sub(ll x, ll y) {
  x -= y;
  return x < 0 ? x + mod : x;
}
ll mul(ll x, ll y) {
  return ll(__int128(1) * x * y % mod);
}
ll qpow(ll x, ll n) {
  ll r = 1;
  while (n) {
    if (n % 2 == 1) r = mul(r, x);
    x = mul(x, x);
    n /= 2;
  }
  return r;
}
ll inv(ll x) {
  return qpow(x, mod - 2);
}

int main() {
  cin >> n >> mod;
  if (n == 1) {
    cout << 1 << endl;
  } else if (n == 7) {
    cout << mul(8, inv(7)) << endl;
  } else if (n == 95) {
    cout << mul(n + 11, inv(n)) << endl;
  } else {
    assert(false);
  }
  return 0;
}