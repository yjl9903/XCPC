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

int n, a[maxn], b[maxn], c[maxn], cnt[maxn];

int cal() {
  for (int i = 1; i <= n; i++) {
    cnt[a[i]]++;
  }
  int r = 0;
  while (cnt[r] > 0) r++;
  for (int i = 1; i <= n; i++) {
    cnt[a[i]]--;
  }
  return r;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      b[i] = a[i];
      c[b[i]]++;
    }

    vector<int> ans;
    for (int i = 1; i <= n; i++) {
      if (c[a[i]] > 1) {
        c[a[i]]--;
        a[i] = cal();
        ans.push_back(i);
        c[a[i]]++;
      }
    }

    int sum = 0;
    for (int i = 1; i <= n; i++) {
      if (a[i] == i - 1) {
        sum++;
      }
    }

    while (sum < n) {
      int tot = cal();
      if (tot == n) {
        for (int i = 1; i <= n; i++) {
          if (a[i] != i - 1) {
            ans.push_back(i);
            tot = a[i];
            a[i] = cal();
            assert(a[i] == n);
            break;
          }
        }
      }
      
      while (tot < n) {
        ans.push_back(tot + 1);
        int src = a[tot + 1];
        a[tot + 1] = cal();
        assert(a[tot + 1] == tot);
        sum++;
        tot = src;
      }
    }
    
    #ifdef XLor
    cout << "a: ";
    for (int i = 1; i <= n; i++) {
      cout << a[i] << ' ';
    }
    cout << endl;
    #endif

    assert(ans.size() <= n + n);
    printf("%d\n", ans.size());
    for (int x: ans) {
      printf("%d ", x);
    }
    puts("");

    for (int i = 0; i <= n; i++) {
      b[i] = c[i] = 0;
    }
  }
  return 0;
}