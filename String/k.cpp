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
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, k, fail[maxn];
bool ans[maxn];
char s[maxn];
vector<int> edge[maxn];

ll ceil(ll x, ll y) {
  return (x + y - 1) / y;
}

int main() {
  scanf("%d%d%s", &n, &k, s + 1);
  if (k == 1) {
    for (int i = 1; i <= n; i++) putchar('1');
    return 0;
  }
  edge[0].push_back(1);
  for (int i = 2; i <= n; i++) {
    int cur = fail[i - 1];
    while (cur && s[cur + 1] != s[i]) cur = fail[cur];
    if (s[cur + 1] == s[i]) cur++;
    fail[i] = cur;
    edge[fail[i]].push_back(i);
  }
  set<int> st;
  function<void(int)> dfs = [&](int u) {
    auto it = st.lower_bound((int)ceil(1ll * u * (k - 1), k));
    int p = u - *it;
    if (it != st.end() && k * p <= u && u <= (k + 1) * p) ans[u] = 1;
    st.insert(u);
    for (int v: edge[u]) dfs(v);
    st.erase(u);
  };
  dfs(0);
  for (int i = 1; i <= n; i++) putchar(ans[i] ? '1' : '0');
  return 0;
}