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

int n, m, ch[maxn][2], deg[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      ch[i][0] = ch[i][1] = -1;
      deg[i] = 0;
    }
    for (int i = 1, u, v; i <= m; i++) {
      scanf("%d%d", &u, &v);
      if (ch[u][0] == -1 || ch[u][0] == v) {
        ch[u][0] = v;
      } else if (ch[u][1] == -1) {
        ch[u][1] = v;
      } else {
        assert(0);
      }
    }
    for (int u = 1; u <= n; u++) {
      if (ch[u][0] != -1) deg[ch[u][0]]++;
      if (ch[u][1] != -1) deg[ch[u][1]]++;
    }
    set<int> ans, cur;
    for (int i = 1; i <= n; i++) {
      if (!deg[i]) cur.insert(i);
    }
    while (!cur.empty()) {
      set<int> nex;
      for (int u: cur) {
        if (ch[u][0] != -1 && !ans.count(ch[u][0])) nex.insert(ch[u][0]);
        if (ch[u][1] != -1 && !ans.count(ch[u][1])) nex.insert(ch[u][1]);
      }
      set<int> nex2;
      for (int u: nex) {
        if (ch[u][0] != -1 && !ans.count(ch[u][0])) nex2.insert(ch[u][0]);
        if (ch[u][1] != -1 && !ans.count(ch[u][1])) nex2.insert(ch[u][1]);
      }
      if (nex.size() < nex2.size()) {
        for (int x: nex) {
          ans.insert(x);
          nex2.erase(x);
        }
        cur = nex2;
      } else {
        cur.clear();
        for (int u: nex2) {
          ans.insert(u);
        }
        for (int u: nex2) {
          if (ch[u][0] != -1 && !ans.count(ch[u][0])) cur.insert(ch[u][0]);
          if (ch[u][1] != -1 && !ans.count(ch[u][1])) cur.insert(ch[u][1]);
        }
      }
    }
    assert(ans.size() * 7 <= n * 4);
    printf("%d\n", ans.size());
    for (int x: ans) {
      printf("%d ", x);
    }
    puts("");
  }
  return 0;
}