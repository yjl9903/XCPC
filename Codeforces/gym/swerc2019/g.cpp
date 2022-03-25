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
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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

int s, l, n, a[maxn], pre[maxn][205];
int sum[205], pos[205];

set<int> edge[205];
vector<int> bag[205];

int main() {
  scanf("%d%d%d", &s, &l, &n);
  vector<string> lsh;
  for (int i = 1; i <= s; i++) {
    char ss[30];
    scanf("%s", ss);
    lsh.push_back(ss);
    for (int j = 1; j <= s; j++) {
      if (i == j) continue;
      edge[i].insert(j);
    }
  }
  sort(begin(lsh), end(lsh));
  auto id = [&](const string& s) {
    return lower_bound(begin(lsh), end(lsh), s) - begin(lsh) + 1;
  };
  for (int i = 1; i <= l; i++) {
    char s[30], t[30];
    scanf("%s%s", s, t);
    int u = id(s), v = id(t);
    edge[u].erase(v);
    edge[v].erase(u);
  }
  for (int i = 1; i <= n; i++) {
    char s[30];
    scanf("%s", s);
    a[i] = id(s);
    bag[a[i]].push_back(i);
    pre[i][a[i]]++;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= s; j++) {
      pre[i][j] += pre[i - 1][j];
    }
  }
  for (int i = 1; i <= s; i++) {
    if (!bag[i].empty()) {
      int p = bag[i][0];
      for (int v: edge[i]) {
        sum[i] += pre[p][v];
      }
      // dbg(i, sum[i]);
    }
  }
  for (int i = 1; i <= n; i++) {
    int choose = -1;
    for (int j = 1; j <= s; j++) {
      if (pos[j] < (int)bag[j].size()) {
        if (sum[j] == 0) {
          choose = j;
          pos[j]++;
          if (pos[j] < (int)bag[j].size()) {
            int R = bag[j][pos[j]], L = bag[j][pos[j] - 1];
            for (int v: edge[j]) {
              auto r = upper_bound(bag[v].begin() + pos[v], bag[v].end(), R);
              auto l = lower_bound(bag[v].begin() + pos[v], bag[v].end(), L);
              sum[j] += r - l;
            }
          }
          for (int v: edge[j]) {
            if (pos[v] < (int)bag[v].size()) {
              sum[v]--;
            }
          }
          break;
        }
      }
    }
    // dbg(choose);
    assert(choose != -1);
    printf("%s%c", lsh[choose - 1].c_str(), i == n ? '\n' : ' ');
  }
  return 0;
}