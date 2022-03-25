#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <map>
#include <functional>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int k, pre[16];
int a[maxn], id[maxn], vis[maxn], fa[maxn], nxt[maxn];
ll sum[16], tag;
map<ll,int> bel;
vector<int> plan[(1 << 15) + 1];

int main() {
  scanf("%d", &k);
  for (int i = 0, n, x; i < k; i++) {
    scanf("%d", &n);
    pre[i + 1] = pre[i] + n;
    for (int j = 0; j < n; j++) {
      scanf("%d", &x);
      a[pre[i] + j] = x;
      id[pre[i] + j] = i;
      bel[x] = pre[i] + j;
      sum[i] += x;
    }
    tag += sum[i];
  }
  if (tag % k) return puts("No"), 0;
  tag /= k;
  for (int i = 0; i < pre[k]; i++) {
    ll need = tag + a[i] - sum[id[i]];
    if (bel.count(need)) nxt[i] = bel[need];
    else nxt[i] = -1;
  }
  for (int i = 0; i < pre[k]; i++) {
    if (vis[i]) continue;
    function<void(int)> dfs = [&](int x) {
      if (vis[x] == i + 1) {
        vector<int> choose(k, -1);
        int y = fa[x], sta = 1 << id[x]; 
        choose[id[x]] = x;
        while (y != x) {
          if (choose[id[y]] != -1) return ;
          choose[id[y]] = y; sta |= 1 << id[y];
          y = fa[y];
        }
        plan[sta] = choose;
        return ;
      }
      vis[x] = i + 1;
      if (nxt[x] == -1) return ;
      fa[nxt[x]] = x;
      dfs(nxt[x]);
    };
    dfs(i);
  }
  int ss = (1 << k) - 1;
  for (int s = 1; s <= ss; s++) {
    if (!plan[s].empty()) continue;
    for (int s2 = s; s2; s2 = (s2 - 1) & s) {
      if (!plan[s2].empty() && !plan[s ^ s2].empty()) {
        for (int x: plan[s2]) plan[s].push_back(x);
        for (int i = 0; i < k; i++) {
          if (plan[s][i] == -1) {
            plan[s][i] = plan[s ^ s2][i];
          }
        }
        break;
      }
    }
  }
  if (plan[ss].empty()) return puts("No"), 0;
  puts("Yes");
  map<ll,int> mp;
  for (int i = 0; i < k; i++) mp[tag + a[plan[ss][i]] - sum[i]] = i + 1;
  for (int i = 0; i < k; i++) {
    printf("%d %d\n", a[plan[ss][i]], mp[a[plan[ss][i]]]);
  }
  return 0;
}