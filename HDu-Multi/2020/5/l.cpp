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
#include <random>
#include <ctime>
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

const int T = 1000000;

mt19937 rnd(time(nullptr));

int n, k, cnt[maxn], vis[maxn];

int gen(int n) {
  return rnd() % n + 1;
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < T; i++) {
    for (int i = 1; i <= n; i++) {
      vis[i] = 0;
    }
    int c = n;
    for (int i = 0; i + k + 1 <= n; i += k + 1) {
      int j = 1;
      while (vis[j]) j++;
      vis[j] = 1;
      c--;
      for (int p = 0; p < k; p++) {
        int tot = 0, pos = gen(c);
        int j = 1;
        while (j <= n) {
          if (!vis[j]) {
            tot++;
            if (tot == pos) {
              vis[j] = 1;
              break;
            }
          }
          j++;
        }
        c--;
      }
    }
    for (int i = 1; i <= n; i++) {
      // cout << vis[i] << ' ';
      if (!vis[i]) {
        cnt[i]++;
      }
    }
    // cout << endl;
  }
  cout << "Cnt:\n";
  for (int i = 1; i <= n; i++) {
    cout << int(1.0 * cnt[i] / T * 12960) << ' ';
  }
  return 0;
}