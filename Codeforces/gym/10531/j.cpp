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

struct Op {
  int l, r, tp;
};

int n, a[maxn], b[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", b + i);
  }
  sort(a + 1, a + 1 + n);
  vector<Op> ans;
  int L = 1, R = n;
  while (L < R) {
    // for (int i = 1; i <= n; i++) cout << a[i] << ' ';
    // cout << endl;
    {
      int pos = -1;
      int cnt0 = 0, cnt1 = 0;
      for (int i = L; i <= R; i++) {
        if (a[i] == b[L]) {
          pos = i;
          break;
        } else if (a[i] < b[L]) {
          cnt0++;
        } else if (a[i] > b[L]) {
          cnt1++;
        }
      }
      // dbg(L, b[L], pos);
      if (pos == L) {
        L++;
        continue;
      }
      if (cnt0 == 0) {
        sort(a + L, a + 1 + pos);
        ans.push_back({ L, pos, 1 });
        L++;
        continue;
      } else if (cnt1 == 0) {
        sort(a + L, a + 1 + pos);
        reverse(a + L, a + 1 + pos);
        ans.push_back({ L, pos, 0 });
        L++;
        continue;
      }
    }
    {
      int pos = -1;
      int cnt0 = 0, cnt1 = 0;
      for (int i = R; i >= L; i--) {
        if (a[i] == b[R]) {
          pos = i;
          break;
        } else if (a[i] < b[R]) {
          cnt0++;
        } else if (a[i] > b[R]) {
          cnt1++;
        }
      }
      // dbg(L, b[L], pos);
      if (pos == R) {
        R--;
        continue;
      }
      if (cnt0 == 0) {
        sort(a + pos, a + 1 + R);
        reverse(a + pos, a + 1 + R);
        ans.push_back({ pos, R, 0 });
        R--;
        continue;
      } else if (cnt1 == 0) {
        sort(a + pos, a + 1 + R);
        ans.push_back({ pos, R, 1 });
        R--;
        continue;
      }
    }
    assert(false);
  }
  assert(ans.size() <= n - 1);
  printf("%d\n", ans.size() + 1);
  printf("1 %d I\n", n);
  for (auto& x: ans) {
    printf("%d %d %c\n", x.l, x.r, x.tp == 1 ? 'I' : 'D');
  }
  return 0;
}