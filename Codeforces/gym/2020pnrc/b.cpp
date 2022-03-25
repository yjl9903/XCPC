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

int n, k, a[maxn], pos[maxn];

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    pos[a[i]] = i;
  }
  vector<int> ans;
  set<int> st;
  for (int i = 1, j = 1; i <= n; i = j) {
    while (j <= n && pos[a[j]] != j) j++;
    int mnp = -1;
    // dbg(i, j);
    for (int k = i; k <= j; k++) {
      if (st.count(a[k])) continue;
      if (mnp == -1 || a[k] < a[mnp]) {
        mnp = k;
      }
    }
    // dbg(mnp);
    pos[a[mnp]] = mnp;
    st.insert(a[mnp]);
    ans.push_back(a[mnp]);
    j = mnp + 1;
    if (ans.size() == k) break;
  }
  for (int x: ans) printf("%d ", x);
  return 0;
}