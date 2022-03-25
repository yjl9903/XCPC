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

char mp[30][30];

int main() {
  int cntB = 0, cntW = 0;
  for (int i = 1; i <= 25; i++) {
    scanf("%s", mp[i] + 1);
    for (int j = 1; j <= 25; j++) {
      if (mp[i][j] == 'x') {
        cntB++;
      } else if (mp[i][j] == 'o') {
        cntW++;
      }
    }
  }
  vector<PII> ans;
  char tot = cntB == cntW ? 'x' : 'o';

  for (int i = 1; i <= 25; i++) {
    for (int j = 1; j <= 21; j++) {
      int cnt = 0;
      for (int k = j; k <= j + 4; k++) {
        cnt += mp[i][k] == tot;
      }
      if (cnt == 4) {
        for (int k = j; k <= j + 4; k++) {
          if (mp[i][k] != tot && mp[i][k] == '.') {
            ans.emplace_back(i, k);
          }
        } 
      }
    }
  }
  for (int i = 1; i <= 25; i++) {
    for (int j = 1; j <= 21; j++) {
      int cnt = 0;
      for (int k = j; k <= j + 4; k++) {
        cnt += mp[k][i] == tot;
      }
      if (cnt == 4) {
        for (int k = j; k <= j + 4; k++) {
          if (mp[k][i] != tot  && mp[k][i] == '.') {
            ans.emplace_back(k, i);
          }
        } 
      }
    }
  }
  for (int i = 1; i <= 21; i++) {
    for (int j = 1; j <= 21; j++) {
      int cnt = 0;
      for (int k = 0; k < 5; k++) {
        cnt += mp[i + k][j + k] == tot;
      }
      if (cnt == 4) {
        for (int k = 0; k < 5; k++) {
          if (mp[i + k][j + k] != tot && mp[i + k][j + k] == '.') {
            ans.emplace_back(i + k, j + k);
          }
        } 
      }
    }
  }
  for (int i = 4; i <= 25; i++) {
    for (int j = 1; j <= 21; j++) {
      int cnt = 0;
      for (int k = 0; k < 5; k++) {
        cnt += mp[i - k][j + k] == tot;
      }
      if (cnt == 4) {
        // dbg(i, j);
        for (int k = 0; k < 5; k++) {
          if (mp[i - k][j + k] != tot && mp[i - k][j + k] == '.') {
            ans.emplace_back(i - k, j + k);
          }
        } 
      }
    }
  }
  
  if (ans.empty()) {
    puts("tie");
  } else {
    sort(begin(ans), end(ans));
    ans.resize(unique(begin(ans), end(ans)) - begin(ans));
    for (auto& x: ans) {
      printf("%d %d\n", x.first - 1, x.second - 1);
    }
  }
  return 0;
}