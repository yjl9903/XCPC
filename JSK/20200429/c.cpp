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

string n;
int k;

void norm(ll& x, ll& y) {
  ll g = __gcd(x, y);
  x /= g; y /= g;
}

int main() {
  cin >> n >> k;
  int pi = 0, x = 0;
  for (; n[pi] != '.'; pi++) {
    x = x * 10 + n[pi] - '0';
  }
  assert(n[pi] == '.');

  ll prefix = atoll(n.substr(0, pi).c_str());

  ll rest = atoll(n.substr(n.length() - k).c_str());

  ll fz = rest, fm = 1;
  for (int i = 1; i <= k; i++) fm *= 10;
  fm--;
  norm(fz, fm);

  if ((int)n.length() - 1 - pi - k > 0) {
    ll othZ = atoll(n.substr(pi + 1,(int)n.length() - 1 - pi - k).c_str()), othM = 1;

    for (int i = 1; i <= (int)n.length() - 1 - pi - k; i++) fm *= 10, othM *= 10;

    norm(fz, fm);
    norm(othZ, othM);
    

    ll a = fz * othM + fm * othZ;
    ll b = fm * othM;
    norm(a, b);

    fz = a; fm = b;
  }
  
  fz += fm * prefix;
  norm(fz, fm);

  cout << fz << '/' << fm << endl;
  return 0;
}