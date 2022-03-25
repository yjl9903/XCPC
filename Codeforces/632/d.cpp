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

int n, k;
char s[maxn];

int main() {
  scanf("%d%d%s", &n, &k, s + 1);
  int sum = 0;
  vector<int> pos;
  for (int i = n, tot = 0; i >= 1; i--) {
    if (s[i] == 'R') {
      sum += n - tot - i;
      pos.push_back(i);
      tot++;
    }
  }
  if (k > sum) {
    puts("-1"); return 0;
  }
  reverse(begin(pos), end(pos));
  vector<vector<int> > ans;
  int del = 0;
  for (int i = 1; i <= k; i++) {
    vector<int> vec, ok(pos.size(), 0); ok.back() = 1;
    int move = 1;
    for (int i = 0; i < (int)pos.size() - 1; i++) {
      if (pos[i] + 1 < pos[i + 1]) {
        ok[i] = true; move++;
      }
    }
    move = min(move, sum - (k - i));
    for (int i = (int)pos.size() - 1; i >= 0; i--) {
      if (!ok[i]) continue;
      vec.push_back(pos[i]);
      pos[i]++; sum--; move--;
      if (move == 0) break;
    }
    if (pos.back() == n - del) {
      pos.pop_back(); del++;
    }
    ans.push_back(vec);
  }
  if (sum) {
    puts("-1"); return 0;
  }
  for (int i = 0; i < k; i++) {
    printf("%d", (int)ans[i].size());
    for (int x: ans[i]) printf(" %d", x);
    puts("");
  }
  return 0;
}