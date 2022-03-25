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

int n, p[maxn];
string words[maxn];

int cal(const string& a, const string& b) {
  for (int i = 0; i < a.size() && i < b.size(); i++) {
    if (a[i] != b[i]) return i;
  }
  return min(a.size(), b.size());
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    p[i] = i;
    cin >> words[i];
  }
  int sum = inf; vector<string> ans;
  do {
    int c = 0;
    for (int i = 1; i < n; i++) {
      c += cal(words[p[i]], words[p[i + 1]]);
    }
    if (c <= sum) {
      vector<string> tot;
      for (int i = 1; i <= n; i++) {
        tot.push_back(words[p[i]]);
      }
      if (c < sum) ans = tot;
      else if (tot < ans) ans = tot;
      sum = c;
    }
  } while (next_permutation(p + 1, p + 1 + n));
  for (auto& s: ans) puts(s.c_str());
  return 0;
}