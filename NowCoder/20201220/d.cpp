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
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 3000000 + 5;

struct fastIO {
  static const int SIZE = 1 << 20;
  char s[SIZE]; int it, len;
  fastIO() { it = len = 0; }
  inline char get() {
    if (it < len) return s[it++];
    it = 0; len = fread(s, 1, SIZE, stdin);
    if (len == 0) return EOF;
    else return s[it++];
  }
  inline bool notend() {
    char c = get();
    while (c == ' ' || c == '\n') c = get();
    if (it > 0) it--;
    return c != EOF;
  }
} buff;
inline int gi() {
  int r = 0; bool ng = 0;
  char c = buff.get();
  while (c != '-' && (c < '0' || c > '9')) c = buff.get();
  if (c == '-') ng = 1, c = buff.get();
  while (c >= '0' && c <= '9') r = r * 10 + c - '0', c = buff.get();
  return ng ? -r : r;
}

int n, m, s, t, ord[maxn];
int uu[maxn], vv[maxn], ww[maxn];
int uu2[maxn], vv2[maxn], ww2[maxn];

int pre[maxn], siz[maxn];
int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int u, int v) {
  u = find(u);
  v = find(v);
  if (u != v) {
    // if (siz[u] > siz[v]) pre[v] = u;
    // else {
    //   if (siz[u] == siz[v]) siz[v]++;  
      pre[u] = v;
    // }
  }
}

int main() {
  scanf("%d%d%d%d", &n, &m, &s, &t);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%d", uu + i, vv + i, ww + i);
    ord[i] = i;
  }
  sort(ord + 1, ord + 1 + m, [&](int x, int y) {
    return ww[x] < ww[y];
  });
  for (int i = 1; i <= m; i++) {
    uu2[i] = uu[ord[i]];
    vv2[i] = vv[ord[i]];
    ww2[i] = ww[ord[i]];
  }
  swap(uu, uu2);
  swap(vv, vv2);
  swap(ww, ww2);
  for (int i = 1; i <= n; i++) {
    pre[i] = i;
    siz[i] = 1;
  }
  int L = -1, R = -1;
  for (int i = m; i >= 1; i--) {
    int u = uu[i];
    int v = vv[i];
    join(u, v);
    if (find(s) == find(t)) {
      L = ww[i];
      break;
    }
  }
  assert(L != -1);
  printf("%d ", L);
  for (int i = 1; i <= n; i++) {
    pre[i] = i;
    siz[i] = 1;
  }
  for (int i = 1; i <= m; i++) {
    if (ww[i] < L) continue;
    int u = uu[i];
    int v = vv[i];
    join(u, v);
    if (find(s) == find(t)) {
      R = ww[i];
      break;
    }
  }
  assert(R != -1);
  printf("%d\n", R);
  return 0;
}