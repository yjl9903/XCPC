#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <map>
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

int k; ll sum[16], tag;
vector<int> a[16];
map<int,int> bel;
map<ll,PII> need;
map<ll,int> show;

vector<int> plan[(1 << 15) + 1];

void get(int b, int x) {
  vector<int> vis(k + 1, 0);
  vector<int> choose(k + 1, -1);
  ll tot = a[b][x];
  vis[b] = 1; choose[b] = x;
  dbg(b, x);
  while (true) {
    if (!need.count(tot)) {
      // illegal
      return ;
    }
    PII nxt = need[tot];
    dbg(tot, nxt.first, nxt.second);
    if (nxt.first == b) {
      // ok
      int sta = 0;
      for (int i = 1; i <= k; i++) if (vis[i]) sta |= 1 << (i - 1);
      plan[sta] = choose;
      dbg(sta);
      return ;
    } else if (vis[nxt.first]) {
      // illegal
      return ;
    } else {
      vis[nxt.first] = 1;
      choose[nxt.first] = nxt.second;
      tot = a[nxt.first][nxt.second];
      dbg(tot);
    }
  }
}

int main() {
  scanf("%d", &k);
  for (int i = 1, n, x; i <= k; i++) {
    scanf("%d", &n);
    while (n--) {
      scanf("%d", &x); 
      a[i].push_back(x);
      bel[x] = i;
      tag += x;
      sum[i] += x;
    }
  }
  if (tag % k) return puts("No"), 0;
  tag /= k;
  for (int i = 1; i <= k; i++) {
    int n = (int)a[i].size();
    for (int j = 0; j < n; j++) {
      ll rest = sum[i] - a[i][j];
      show[tag - rest]++;
      need[tag - rest] = { i, j };
      dbg(tag - rest, i, j);
    }
  }
  for (auto& x: show) {
    if (x.second > 1) {
      need.erase(x.first);
    }
  }
  for (int i = 1; i <= k; i++) {
    int n = (int)a[i].size();
    for (int j = 0; j < n; j++) {
      get(i, j);
    }
  }
  int ss = (1 << k) - 1;
  for (int s = 1; s <= ss; s++) {
    if (!plan[s].empty()) continue;
    for (int s2 = s; s2; s2 = (s2 - 1) & s) {
      if (!plan[s2].empty() && !plan[s ^ s2].empty()) {
        for (int x: plan[s2]) plan[s].push_back(x);
        for (int i = 1; i <= k; i++) {
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
  for (int i = 1; i <= k; i++) {
    dbg(plan[ss][i]);
  }
  return 0;
}