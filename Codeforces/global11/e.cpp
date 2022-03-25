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

ll exgcd(ll a, ll b, ll& x, ll& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll r = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return r;
}

struct Node {
  char op;
  ll x, y;

  void print() const {
    printf("%I64d %C %I64d\n", x, op, y);
  }
};

int n;
vector<Node> ans;

void get(ll x, ll n) {
  int hBit = 63 - __builtin_clzll(n);
  ll y = x;
  for (int i = 0; i < hBit; i++) {
    ans.push_back(Node { '+', y, y });
    y += y;
  }
  ll r = -1;
  for (int i = 0; i <= hBit; i++) {
    if (n >> i & 1) {
      if (r == -1) {
        r = x << i;
      } else {
        ans.push_back(Node { '+', r, x << i });
        r += x << i;
      }
    }
  }
}

int main() {
  scanf("%d", &n);

  int hBit = 31 - __builtin_clz(n);
  ll x = n, y = n;
  for (int i = 0; i < hBit; i++) {
    ans.push_back(Node { '+', x, x });
    x += x;
  }
  ans.push_back(Node { '^', x, n });
  x ^= n;

  ll a, b;
  exgcd(y, x, a, b);
  if (a < 0) {
    a = -a;
    swap(a, b);
    swap(x, y);
  } else if (b < 0) {
    b = -b;
  }
  if (b % 2) {
    a += x;
    b += y;
  }
  get(y, a);
  get(x, b);
  ans.emplace_back(Node { '^', a * y, b * x });

  printf("%d\n", ans.size());
  for (const Node& x: ans) {
    x.print();
  }
  return 0;
}