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

int n, a[maxn], b[maxn], pos[maxn];

vector<int> trans(vector<int>& op) {
  vector<int> op2;
  int i = 0;
  for (int x: op) {
    if (x) {
      op2.push_back(x);
      int m = n - i - x;
      while (x--) {
        m++;
        i++;
        b[m] = a[i];
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    a[i] = b[i];
  }
  return op2;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  vector< vector<int> > ans;
  while (!is_sorted(a + 1, a + 1 + n)) {
    for (int i = 1; i <= n; i++) {
      pos[a[i]] = i;
    }
    int x = 1;
    while (pos[x] < pos[x + 1]) x++;
    int y = x + 1;
    while (y < n && pos[y + 1] == pos[y] + 1) y++;
    
    vector<int> op = {
      pos[x + 1] - 1,
      pos[y] - pos[x + 1] + 1,
      pos[x] - pos[y],
      n - pos[x]
    };
    ans.push_back(trans(op));

    #ifdef XLor
      for (int i = 1; i <= n; i++) cout << a[i] << ' ';
      cout << endl;
    #endif
  }

  printf("%d\n", ans.size());
  for (const auto& v: ans) {
    printf("%d", v.size());
    for (int x: v) printf(" %d", x);
    puts("");
  }
  return 0;
}