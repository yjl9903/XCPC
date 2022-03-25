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

int n, a[maxn], b[maxn], c[maxn];

vector<int> trans(vector<int>& op) {
  vector<int> op2;
  int i = 0;
  for (int x: op) {
    if (x) {
      dbg(x);
      op2.push_back(x);
      int m = n - i - x;
      while (x--) {
        m++;
        i++;
        c[m] = b[i];
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    b[i] = c[i];
  }
  return op2;
}

vector< vector<int> > solve(bool& flag, bool ap = false) {
  vector< vector<int> > ans;
  for (int i = 1; i <= n; i++) {
    b[i] = a[i];
  }
  for (int i = 2; i <= n; i++) {
    int L = -1, R = -1;
    int pos = -1;
    for (int j = 1; j <= n; j++) {
      if (b[j] == 1) L = j;
      if (b[j] == i - 1) R = j;
      if (b[j] == i) pos = j;
    }
    dbg(pos, L, R);
    if (pos == R + 1) {

    } else if (pos < L) {
      vector<int> tot = {
        pos - 1, L - pos, R - L + 1, n - R
      };
      ans.push_back(trans(tot));
    } else {
      // flag = false;
      // return ans;
      vector<int> tot = {
        R, n - R
      };
      ans.push_back(trans(tot));
      i--;
    }

    // for (int i = 1; i <= n; i++) cout << b[i] << ' ';
    // cout << endl;
  }
  for (int i = 1; i <= n; i++) assert(i == b[i]);
  if (ap) {
    vector<int> v;
    for (int i = 1; i <= n; i++) {
      v.push_back(1);
    }
    ans.push_back(v);
  }
  if (ans.size() > n) flag = false;
  return ans;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    b[i] = a[i];
  }
  bool f1 = true, f2 = true;
  auto r1 = solve(f1);
  for (int i = 1; i <= n; i++) a[i] = n - a[i] + 1;
  auto r2 = solve(f2, true);
  if (f1) {
    printf("%d\n", r1.size());
    for (const auto& v: r1) {
      printf("%d", v.size());
      for (int x: v) printf(" %d", x);
      puts("");
    }
  } else if (f2) {
    printf("%d\n", r2.size());
    for (const auto& v: r2) {
      printf("%d", v.size());
      for (int x: v) printf(" %d", x);
      puts("");
    }
  } else {
    assert(false);
  }
  return 0;
}