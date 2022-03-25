#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <ctime>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <set>
#include <random>
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
using ull = unsigned long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

int n, k, a[maxn], ok[maxn];
ull key[maxn], pre[maxn];

int main() {
  mt19937_64 rnd(time(nullptr));
  ull allH = 0ull;
  for (int i = 1; i < maxn; i++) {
    key[i] = rnd();
  }
  auto check = [&](int l, int r) {
    return (pre[r] ^ pre[l - 1]) == allH;
  };

  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    bool flag = true;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      ok[i] = false;
      if (a[i] > k) {
        flag = false;
      }
    }
    if (!flag) {
      puts("NO");
      continue;
    }

    ok[n + 1] = true;
    set<int> st;
    int R = n;
    for (int i = n; i >= 1; i--) {
      if (st.count(a[i])) {
        break;
      }
      st.insert(a[i]);
      ok[i] = true;
      R = i;
    }
    if (k >= n) {
      // if (R == 1) {
      //   puts("YES");
      // } else {
      //   puts("NO");
      // }
      set<int> st2;
      bool ans = true;
      for (int i = 1; i < R; i++) {
        if (st2.count(a[i])) {
          ans = false;
          break;
        }
        st2.insert(a[i]);
      }
      if (ans) {
        puts("YES");
      } else {
        puts("NO");
      }
      continue;
    }

    for (int i = 1; i <= n; i++) {
      assert(a[i] <= k && a[i] <= n);
      pre[i] = pre[i - 1] ^ key[a[i]];
    }
    allH = 0ull;
    for (int i = 1; i <= k; i++) {
      allH ^= key[i];
    }

    set<int> st2;
    for (int i = R - 1; i >= 1; i--) {
      if (i + k - 1 <= n && check(i, i + k - 1)) {
        ok[i] = ok[i + k];
      } else {
        ok[i] = false;
      }
    }

    st.clear();
    bool ans = false;
    for (int i = 1; i < n; i++) {
      if (st.count(a[i])) {
        break;
      }
      st.insert(a[i]);
      if (ok[i + 1]) {
        ans = true;
        break;
      }
    }
    if (ans) {
      puts("YES");
    } else {
      puts("NO");
    }
  }
  return 0;
}