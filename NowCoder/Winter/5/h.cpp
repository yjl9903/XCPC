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
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int mod = 998244353;
char s[10];

int Hash(const char s[]) {
  int res = 0;
  for (int i = 0; i < 6; i++) {
    res = (1ll * res * 26 + s[i] - 'a') % mod; 
  }
  return res;
}

int main() {
  while (scanf("%s%d", s, &mod) == 2) {
    int hs = Hash(s);
    string stk, ans; bool ok = false;
    function<void(int,int,int)> dfs = [&](int u, int lim, int val) {
      if (ok) return ;
      if (u == 6) {
        if (stk == string(s)) return ;
        if (val == hs) {
          ans = stk; ok = true;
        }
        return ;
      }
      for (char i = lim ? s[u] : 'a'; i < 'z'; i++) {
        stk.push_back(i);
        int tot = (1ll * val * 26 + i - 'a') % mod;
        dfs(u + 1, lim && i == s[u], tot);
        stk.pop_back();
        if (ok) return ;
      }
    };
    dfs(0, true, 0);
    if (ok) {
      assert(ans > string(s));
      assert(hs == Hash(ans.c_str()));
      puts(ans.c_str());
    } else {
      puts("-1");
    }
  }
  return 0;
}