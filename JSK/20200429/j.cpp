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

int a, b, k;

bool check(int x, int k) {
  vector<int> vec;
  while (x) {
    vec.push_back(x % k);
    x /= k;
  }
  for (int i = 0; i < (int)vec.size() - 1 - i; i++) {
    if (vec[i] != vec[(int)vec.size() - 1 - i]) {
      return false;
    }
  }
  return true;
}

int main() {
  cin >> a >> b >> k;
  vector<int> vec;
  for (int i = a; i <= b; i++) vec.push_back(i);
  for (int t = 2; t <= k; t++) {
    vector<int> v;
    for (int x: vec) {
      if (check(x, t)) {
        v.push_back(x);
      }
    }
    vec = v;
    if (vec.empty()) break;
  }
  cout << vec.size() << endl;
  return 0;
}