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

int n, ans[maxn], suf[maxn];
char s[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%s", &n, s + 1);
    vector<pair<char,int> > v;
    for (int i = 1, j = 1; i < n; i = j) {
      while (j < n && s[i] == s[j]) j++;
      v.emplace_back(s[i], j - i + (i == 1));
    }

    set<int> st;
    for (int i = 1; i <= n; i++) st.insert(i);

    int pos = 1;
    if (s[1] == '<') {
      auto x = v[0];
      for (int i = pos + x.second - 1; i >= pos; i--) {
        auto it = st.end(); it--;
        ans[i] = *it; st.erase(it);
      }
      pos += x.second;
    }
    for (int tot = s[1] == '<'; tot + 1 < (int)v.size(); tot += 2) {
      int k = v[tot].second + v[tot + 1].second;
      while (k--) {
        auto it = st.end(); it--;
        if (k + 1 > v[tot].second) {
          ans[pos + k] = *it;
        } else {
          ans[pos + v[tot].second - k - 1] = *it;
        }
        st.erase(it);
      }
      pos += v[tot].second + v[tot + 1].second;
    }
    if (v.back().first == '<') {
      for (int i = pos; i <= n; i++) {
        ans[i] = *st.begin(); st.erase(st.begin());
      }
    } else {
      for (int i = pos; i <= n; i++) {
        auto it = st.end(); it--;
        ans[i] = *it; st.erase(it);
      }
    }
    for (int i = 1; i <= n; i++) {
      printf("%d ", ans[i]);
    }
    puts("");

    assert(st.empty());
    for (int i = 1; i <= n; i++) st.insert(i);
    pos = 1;
    if (s[1] == '>') {
      auto x = v[0];
      for (int i = pos + x.second - 1; i >= pos; i--) {
        auto it = st.begin();
        ans[i] = *it; st.erase(it);
      }
      pos += x.second;
    }
    for (int tot = s[1] == '>'; tot + 1 < (int)v.size(); tot += 2) {
      int k = v[tot].second + v[tot + 1].second;
      while (k--) {
        auto it = st.begin();
        if (k + 1 > v[tot].second) {
          ans[pos + k] = *it;
        } else {
          ans[pos + v[tot].second - k - 1] = *it;
        }
        st.erase(it);
      }
      pos += v[tot].second + v[tot + 1].second;
    }
    if (v.back().first == '<') {
      for (int i = pos; i <= n; i++) {
        ans[i] = *st.begin(); st.erase(st.begin());
      }
    } else {
      for (int i = pos; i <= n; i++) {
        auto it = st.end(); it--;
        ans[i] = *it; st.erase(it);
      }
    }
    for (int i = 1; i <= n; i++) {
      printf("%d ", ans[i]);
    }
    puts("");
  }
  return 0;
}