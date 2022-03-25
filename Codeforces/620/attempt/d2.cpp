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
const int maxn = 100000 + 5;

int n, ans[maxn];
char s[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%s", &n, s + 1);

    set<int> st;
    for (int i = 1; i <= n; i++) st.insert(i);
    for (int i = 1, j; i < n; i = j) {
      j = i;
      while (j < n && s[j] == s[i]) j++;
      vector<int> v;
      for (int k = i; k < j; k++) {
        auto it = st.end(); it--;
        v.push_back(*it);
        st.erase(it);
      }
      if (s[i] == '<') {
        sort(begin(v), end(v));
      } else {
        sort(v.rbegin(), v.rend());
      }
      for (int k = i; k < j; k++) {
        ans[k + 1] = v[k - i];
      }
    }
    for (int i = 1; i <= n; i++) {
      printf("%d ", ans[i]);
    }
    puts("");
    // int l = 1;
    // while (l < n && s[l] == s[1]) l++;
    // if (s[1] == '<') {
    //   if (l < n) l++;
    //   for (int i = 1; i <= l; i++) {
    //     ans[i] = n - l + i;
    //     st.erase(ans[i]);
    //   }
    // } else {
    //   if (l < n) l++;
    //   for (int i = 1; i <= l; i++) {
    //     ans[i] = n + 1 - i;
    //     st.erase(ans[i]);
    //   }
    // }


  }
  return 0;
}