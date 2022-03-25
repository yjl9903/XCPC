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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;
 
int n, siz[maxn], son[maxn];
ll ans[maxn];
vector<int> edge[maxn];
 
void getsz(int u) {
  siz[u] = 1;
  for (int v: edge[u]) {
    getsz(v); siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}
 
struct DS {
  set<int> st;
  ll ans = 0;
  void push(int x) {
    assert(st.find(x) == st.end());
    auto it = st.upper_bound(x);
    int nx = -1, pr = -1;
    if (it != st.end()) {
      ans += 1ll * (*it - x) * (*it - x);
      nx = *it;
    }
    if (it != st.begin()) {
      it--; ans += 1ll * (*it - x) * (*it - x);
      pr = *it;
    }
    st.insert(x);
    if (nx != -1 && pr != -1) {
      ans -= 1ll * (nx - pr) * (nx - pr);
    }
  }
  void pop(int x) {
    assert(st.find(x) != st.end());
    st.erase(x);
    auto it = st.upper_bound(x);
    int nx = -1, pr = -1;
    if (it != st.end()) {
      ans -= 1ll * (*it - x) * (*it - x);
      nx = *it;
    }
    if (it != st.begin()) {
      it--; ans -= 1ll * (*it - x) * (*it - x);
      pr = *it;
    }
    if (nx != -1 && pr != -1) {
      ans += 1ll * (nx - pr) * (nx - pr);
    }
  }
} h;
 
bool sk[maxn];
void add(int u, int tp) {
  if (tp == 1) {
    h.push(u);
  } else if (tp == -1) {
    h.pop(u);
  }
  for (int v: edge[u]) if (!sk[v]) add(v, tp);
}
void dfs(int u, int tp) {
  for (int v: edge[u]) {
    if (v == son[u]) continue;
    dfs(v, 0);
  }
  if (son[u]) dfs(son[u], 1), sk[son[u]] = true;
  add(u, 1); sk[son[u]] = false;
  ans[u] = h.ans;
  if (!tp) add(u, -1);
}
 
int main() {
  scanf("%d", &n);
  for (int i = 2, p; i <= n; i++) {
    scanf("%d", &p);
    edge[p].push_back(i);
  }
  getsz(1); dfs(1, 1);
  for (int i = 1; i <= n; i++) printf("%I64d\n", ans[i]);
  return 0;
}