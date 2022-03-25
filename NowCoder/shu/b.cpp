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



int main() {
  int n;
  vector<tuple<int,int,int> > vec;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int date, num; double temp;
    cin >> date >> num >> temp;
    int tem = int(temp * 10);
    if (tem >= 380) {
      vec.emplace_back(date, tem, -num);
    }
  }
  sort(begin(vec), end(vec), greater<tuple<int,int,int> >());
  printf("%d\n", (int)vec.size());
  for (auto& x: vec) {
    int date, tem, num; tie(date, tem, num) = x;
    printf("%d %d %d.%d\n", date, -num, tem / 10, tem % 10);
  }
  return 0;
}