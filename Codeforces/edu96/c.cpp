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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    multiset<int> st;
    for (int i = 1; i <= n; i++) {
      st.insert(i);
    }
    vector<PII> ans;
    while (st.size() > 1) {
      auto it = st.end();
      it--;
      int x = *it;
      it--;
      int y = *it;
      st.erase(st.find(x));
      st.erase(st.find(y));
      ans.emplace_back(x, y);
      int z = (x + y + 1) / 2;
      st.insert(z);
    }
    printf("%d\n", *st.begin());
    for (auto x: ans) {
      printf("%d %d\n", x.first, x.second);
    }
  }
  return 0;
}