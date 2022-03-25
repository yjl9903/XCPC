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
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

map<string,int> id;
int getID(const string& s) {
  if (id.count(s)) {
    return id[s];
  } else {
    return id[s] = id.size() + 1;
  }
}

int n, q, evId, tail[maxn];
ll ans[maxn];

struct Event {
  int time, val, fa;
  Event(int a = 0, int b = 0, int c = 0) {
    time = a; val = b; fa = c;
  }
} evs[maxn];
vector<int> edge[maxn];

struct Query {
  int l, r, id;
};
vector<Query> que[maxn];

struct Bit {
  ll a[maxn];
  void add(int i, int x) {
    if (!x) return ;
    for (; i <= n; i += i & -i) a[i] += x;
  }
  ll query(int i) {
    ll r = 0;
    for (; i; i -= i & -i) r += a[i];
    return r;
  }
  ll query(int l, int r) {
    return query(r) - query(l - 1);
  }
} f;

void dfs(int u) {
  if (u) {
    f.add(evs[u].time, evs[u].val);
  }
  for (const Query& q: que[u]) {
    ans[q.id] = f.query(q.l, q.r);
  }
  for (int v: edge[u]) {
    dfs(v);
  }
  if (u) {
    f.add(evs[u].time, -evs[u].val);
  }
}


int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    char cmd[20], id[20];
    scanf("%s%s", cmd, id);
    int u = getID(id);
    if (cmd[0] == 'n') {

    } else if (cmd[0] == 'c') {
      int val; scanf("%d", &val);
      evId++;
      edge[tail[u]].push_back(evId);
      evs[evId].time = i;
      evs[evId].val = val;
      tail[u] = evId;
    } else if (cmd[0] == 'b') {
      char id2[20]; scanf("%s", id2);
      int v = getID(id2);
      evId++;
      edge[tail[u]].push_back(evId);
      evs[evId].time = i;
      evs[evId].val = 0;
      tail[v] = evId;
    }
  }
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    int l, r; char id[20];
    scanf("%d%d%s", &l, &r, id);
    if (!::id.count(id)) {
      ans[i] = 0;
    } else {
      int u = getID(id);
      que[tail[u]].push_back((Query){ l, r, i });
    }
  }
  dfs(0);
  for (int i = 1; i <= q; i++) {
    printf("%lld\n", ans[i]);
  }
  return 0;
}