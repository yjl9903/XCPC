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
const int maxn = 2000000 + 5;

struct Ope {
  int tp, a, b;
} q[maxn];

int n, m, cnt, pre[maxn], siz[maxn], fx[maxn], ans[maxn];
vector<int> edge[maxn];

int find(int x) {
  x = fx[x];
  while (x != pre[x]) x = pre[x];
  return x;
}
vector< tuple<int,int,int> > sta;
int join(int x, int y) {
  x = find(x); y = find(y);
  if (x == y) return 0;
  if (siz[x] > siz[y]) swap(x, y);
  pre[x] = y; siz[y] += siz[x];
  sta.push_back((tuple<int,int,int>){ 0, x, y });
  return 1;
}
int del(int x) {
  int y = fx[x];
  siz[find(y)]--;
  fx[x] = ++cnt;
  pre[cnt] = cnt;
  siz[cnt] = 1;
  sta.push_back((tuple<int,int,int>){ 1, x, y });
  return 1;
}
void undo() {
  int tp, a, b;
  tie(tp, a, b) = sta.back(); sta.pop_back();
  if (tp == 0) {
    pre[a] = a; siz[b] -= siz[a];
  } else if (tp == 1) {
    siz[fx[a]]--;
    fx[a] = b;
    siz[find(b)]++;
  }
}

void dfs(int u) {
  int flag = 0;
  if (q[u].tp == 1) {
    flag += join(q[u].a, q[u].b);
  } else if (q[u].tp == 2) {
    flag += del(q[u].a);
  } else if (q[u].tp == 3) {
    flag += del(q[u].a);
    flag += join(q[u].a, q[u].b);
  } else if (q[u].tp == 4) {
    if (find(q[u].a) == find(q[u].b)) ans[u] = 1;
  } else if (q[u].tp == 5) {
    ans[u] = siz[find(q[u].a)];
  }
  for (int v: edge[u]) dfs(v);
  while (flag--) undo();
}

int main() {
  scanf("%d%d", &n, &m);
  cnt = n;
  for (int i = 1; i <= n; i++) {
    pre[i] = i; siz[i] = 1;
    fx[i] = i;
  }
  for (int i = 1, k; i <= m; i++) {
    scanf("%d%d", &q[i].tp, &k);
    if (q[i].tp == 2 || q[i].tp == 5) {
      scanf("%d", &q[i].a);
    } else {
      scanf("%d%d", &q[i].a, &q[i].b);
    }
    edge[k].push_back(i);
  }
  dfs(0);
  for (int i = 1; i <= m; i++) {
    if (q[i].tp == 4) {
      puts(ans[i] ? "Yes" : "No");
    } else if (q[i].tp == 5) {
      printf("%d\n", ans[i]);
    }
  }
  return 0;
}