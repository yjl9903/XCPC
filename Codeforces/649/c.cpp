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

int n, a[maxn], b[maxn], last[maxn], vis[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    last[a[i]] = i;
  }
  set<int> st;
  for (int i = 0; i <= n + 1; i++) {
    if (last[i] == 0) {
      st.insert(i);
    }
  }
  for (int i = 1; i <= n; i++) {
    if (!st.empty()) {
      auto it = st.begin();
      b[i] = *it;
      st.erase(it);
    } else {
      b[i] = n + 1;
    }
    if (i == last[a[i]]) {
      st.insert(a[i]);
    }
  }
  int r = 0;
  for (int i = 1; i <= n; i++) {
    vis[b[i]] = true;
    while (vis[r]) r++;
    if (r != a[i]) {
      puts("-1");
      return 0;
    }
  }
  for (int i = 1; i <= n; i++) printf("%d ", b[i]);
  return 0;
}