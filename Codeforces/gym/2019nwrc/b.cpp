#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <cassert>
#include <ctime>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const double pi = acos(-1.0);
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n;

double msin(double x) {
  double r = fmod(fmod(x, 2 * pi) + 2 * pi, 2 * pi);
  if (r < pi / 2) return r;
  if (r < pi / 2 * 3) return pi - r;
  return r - pi * 2;
}

int main() {
  scanf("%d", &n);
  if (n == 1) return puts("1"), 0;
  if (n == 2) return puts("1"), puts("2"), 0;
  const double eps = 1e-3;
  int l = -1000000689, r = 1000000001;
  double last = msin(r);
  vector<int> ans = { l, r };
  for (int i = 3; i <= n; i++) {
    int f = 0;
    if (i % 2 == 1) {
      for (int j = l + 1; j <= r; j++) {
        double s = msin(j);
        if (s < last && s >= last - eps) {
          last = s;
          ans.push_back(j);
          l = j;
          f = 1;
          break;
        }
        if (last > 0 && s < 0) j++;
        else if (last < 0 && s > 0) j++;
      }
    } else {
      for (int j = r - 1; j >= l; j--) {
        double s = msin(j);
        if (s < last && s >= last - eps) {
          last = s;
          ans.push_back(j);
          r = j;
          f = 1;
          break;
        }
        if (last > 0 && s < 0) j--;
        else if (last < 0 && s > 0) j--;
      }
    }
    assert(f);
  }
  for (int x: ans) printf("%d\n", x);
  // for (int i = 0; i < n; i++) {
  // if (i % 200 == 0) printf("%d,", ans[i]);
  // printf("%d,", ans[i]);
  // }
  return 0;
}