#include <algorithm>
#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using ll = long long;
using namespace std;
const int N = 6e6 + 10;
const int Mod = 998244353;
ll a[N];
int n, m, T;
int Read();
ll dis[N], vis[N];
int fir[N], to[N], val[N], nxt[N], tot = 1;
void add(int u, int v, int z) {
  nxt[++tot] = fir[u], fir[u] = tot, to[tot] = v, val[tot] = z;
}
struct nodde {
  int p;
  ll w;
  nodde(int a, ll b) : p(a), w(b) {}
  bool operator<(const nodde& b) const { return w > b.w; }
};
priority_queue<nodde> que;
void Dj1() {
  for (int i = 1; i <= 20 * n; i++) dis[i] = -1, vis[i] = 0;
  que.push({1, 0ll});
  dis[1] = 0;
  while (!que.empty()) {
    int k = que.top().p;
    que.pop();
    for (int e = fir[k]; e; e = nxt[e]) {
      int Nxt = to[e];
      if (dis[Nxt] == -1 || dis[Nxt] > dis[k] + val[e]) {
        dis[Nxt] = dis[k] + val[e];
        if (!vis[Nxt]) que.push({Nxt, dis[Nxt]});
      }
    }
  }
}
ll fir1[N], nxt1[N], to1[N], tot1 = 1;
pair<int, int> f[N];
void add1(int u, int v, int z, int w) {
  nxt1[++tot1] = fir1[u];
  to1[tot1] = v, fir1[u] = tot1;
  f[tot1] = {z, w};
}
struct node {
  int A, B;
  bool operator<(const node& r) const {
    // if (A >= 20 && r.A >= 20) {
      if (A == r.A) return B < r.B;
      return A < r.A;
    // } else if (A >= 20) {
    //   return false;
    // } else if (r.A >= 20) {
    //   return true;
    // } else {
    //   return B + (1 << A) < r.B + (1 << r.A);
    // }
  }
  bool operator>(const node& r) const {
    return r < *this;
  }
  bool cmp(const node& r) const {
    if (A >= 20 && r.A >= 20) {
      if (A == r.A) return B < r.B;
      return A < r.A;
    } else if (A >= 20) {
      return false;
    } else if (r.A >= 20) {
      return true;
    } else {
      return B + (1 << A) < r.B + (1 << r.A);
    }
  }
} dx[N];
priority_queue<pair<node, int>, vector<pair<node, int> >,
               greater<pair<node, int> > >
    q;
void dj2() {
  int inf = 1e9;
  for (int i = 1; i <= 2 * n + 2; i++) dx[i] = {inf, inf}, vis[i] = 0;
  dx[1] = {0, 0};
  q.push({dx[1], 1});
  while (!q.empty()) {
    int k = q.top().second;
    q.pop();
    if (vis[k]) continue;
    vis[k] = true;
    for (int e = fir1[k]; e; e = nxt1[e]) {
      int Nxt = to1[e];
      node hhh = {dx[k].A + f[e].first, dx[k].B + f[e].second};
      if (hhh < dx[Nxt]) {
        dx[Nxt] = hhh;
        q.push({dx[Nxt], Nxt});
      }
    }
  }
}
long long Pow(ll u, int v) {
  long long num = 1;
  for (; v; v /= 2, (u *= u) %= Mod)
    if (v & 1) (num *= u) %= Mod;
  return num;
}
int main() {
  n = Read(), m = Read();
  for (int i = 1; i <= n; i++) add1(i, i + n, 1, 0), add1(i + n, i, 1, 0);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= 18; j++) add(i + n * (j - 1), i + j * n, 1ll << (j - 1));
  for (int i = 1; i <= m; i++) {
    int x = Read(), y = Read();
    add(x, y, 1);
    add1(x, y, 0, 1);
    add1(y + n, x + n, 0, 1);
    for (int j = 1; j <= 18; j++) {
      if (j & 1)
        add(y + j * n, x + j * n, 1);
      else
        add(x + j * n, y + j * n, 1);
    }
  }
  ll ans = -1;
  Dj1();
  for (int i = 0; i <= 19; i++)
    if (ans == -1)
      ans = dis[n + i * n];
    else if (dis[n + i * n] != -1)
      ans = min(ans, dis[n + i * n]);
  if (ans != -1) {
    printf("%lld\n", ans % Mod);
    return 0;
  }
  dj2();
  assert(dx[n].A >= 1 && dx[n * 2].A >= 1);
  if (dx[n].cmp(dx[2 * n]))
    ans = Pow(2, dx[n].A) + dx[n].B - 1;
  else
    ans = Pow(2, dx[2 * n].A) + dx[2 * n].B - 1;
  // else
  //   ans = Pow(2, dx[n].A) + min(dx[n].B, dx[n * 2].B) - 1;
  printf("%lld\n", ans);
  return 0;
}

int Read() {
  int val = 0, opt = 1;
  char ch;
  while (!isdigit(ch = getchar()))
    if (ch == '-') opt = -1;
  while (isdigit(ch)) (val *= 10) += ch - '0', ch = getchar();
  return val * opt;
}