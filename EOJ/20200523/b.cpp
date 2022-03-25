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

int n;
char ans[maxn];

bool query(const string& s) {
  cout << "? " << s << endl;
  int x; cin >> x;
  return x;
}

void ok(const string& s) {
  cout << "! " << s << endl;
}

void solve(int a, int b, char c1, char c2) {
  string tot;
  for (int i = 0; i < a; i++) tot += c1;
  for (int i = 0; i + (int)tot.length() < n; i++) {
    
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin >> n;
  int ans0 = -1, ans1 = -1, l = 1, r = (n / 2) + 1;
  while (l <= r) {
    int m = (l + r) / 2;
    string s;
    for (int i = 0; i < m; i++) s += '0';
    if (query(s)) {
      ans0 = m; l = m + 1;
    } else {
      r = m - 1;
    }
  }
  l = 1; r = (n / 2) + 1;
  while (l <= r) {
    int m = (l + r) / 2;
    string s;
    for (int i = 0; i < m; i++) s += '1';
    if (query(s)) {
      ans1 = m; l = m + 1;
    } else {
      r = m - 1;
    }
  }
  if (ans0 == -1) {
    string s;
    for (int i = 0; i < n; i++) s += '1';
    ok(s); return 0;
  } else if (ans1 == -1) {
    string s;
    for (int i = 0; i < n; i++) s += '0';
    ok(s); return 0;
  }
  int cnt0 = 0, cnt1 = 0;
  if (ans0 < ans1) {
    cnt0 = ans0; cnt1 = n - cnt0;
  } else {
    cnt1 = ans1; cnt0 = n - cnt1;
  }
  if (cnt0 <= cnt1) {
    solve(cnt0, cnt1, '0', '1');
  } else {
    solve(cnt1, cnt0, '1', '0');
  }
  return 0;
}