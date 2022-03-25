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

int n, a[maxn], cnt[maxn], nxt[maxn], pos[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    multiset<int> st;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      cnt[i] = 1; pos[a[i]] = i;
      st.insert(1);
    }
    vector<int> stk;
    for (int i = n; i >= 1; i--) {
      while (!stk.empty() && a[stk.back()] < a[i]) stk.pop_back();
      if (stk.empty()) {
        nxt[i] = -1;
      } else {
        nxt[i] = stk.back();
      }
      stk.push_back(i);
    }
    bool flag = true;
    for (int i = 1; i <= n; i++) {
      int x = pos[i];
      auto it = st.find(cnt[x]);
      // dbg(i, cnt[x]);
      if (*it != *st.rbegin()) {
        flag = false; break;
      }
      st.erase(st.find(cnt[x]));
      if (nxt[x] != -1) {
        st.erase(st.find(cnt[nxt[x]]));
        cnt[nxt[x]] += cnt[x];
        st.insert(cnt[nxt[x]]);
      }
    }
    puts(flag ? "Yes" : "No");
  }
  return 0;
}