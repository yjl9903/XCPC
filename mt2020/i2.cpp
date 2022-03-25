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
using ull = unsigned long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

ull ran() {
	static ull x = 233;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	return x;
}

int main() {
  const int T = 10000000;
  set<ull> st;
  for (int i = 0; i < T; i++) {
    ull x = ran();
    if (st.count(x)) {
      dbg(i, x);
      break;
    }
    st.insert(x);
  }
  return 0;
}