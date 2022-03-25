#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <list>
#include <time.h>
#include <math.h>
#include <random>
#include <deque>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <chrono>
#include <cstring>

using namespace std;

typedef long long ll;

#ifdef ONPC
  mt19937 rnd(228);
#else
  mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
#endif

const int N = 2e3 + 7;
const int M = 228228239;
const int inv_2 = (M + 1) / 2;

inline int add(int a, int b)
{
  a += b;
  if (a < 0) a += M;
  if (a >= M) a -= M;
  return a;
}

inline int mul(int a, int b)
{
  return (a * (ll) b) % M;
}

vector <int> g[N];
vector <int> up[N];

int dp[N][N][2];
int h[N];
int cur[N][2];
int go[N][2];
int a[N][2], b[N][2], c[N][2];

void convolution(int n)
{
  for (int i = n - 1; i >= 0; i--)
  {
    for (int t = 0; t < 2; t++)
    {
      a[i][t] = add(a[i][t], a[i + 1][t]);
      b[i][t] = add(b[i][t], b[i + 1][t]);
    }
  }
  for (int i = 0; i <= n; i++)
  {
    for (int x = 0; x < 2; x++)
    {
      for (int y = 0; y < 2; y++)
      {
        c[i][x ^ y] = add(c[i][x ^ y], mul(a[i][x], b[i][y]));
      }
    }
  }
  for (int i = 0; i < n; i++)
  {
    for (int t = 0; t < 2; t++)
    {
      c[i][t] = add(c[i][t], -c[i + 1][t]);
    }
  }
}

void dfs(int v, int pr)
{
  for (int to : g[v])
  {
    if (to != pr)
    {
      h[to] = h[v] + 1;
      dfs(to, v);
    }
  }
  for (int i = 0; i <= h[v]; i++)
  {
    for (int t = 0; t < 2; t++)
    {
      cur[i][t] = 0;
    }
  }
  cur[h[v]][0] = 1;
  for (int to : g[v])
  {
    if (to != pr)
    {
      for (int i = 0; i <= h[v]; i++)
      {
        for (int t = 0; t < 2; t++)
        {
          go[i][t] = 0;
        }
      }
      auto f = [&] (int me, int me_t, int he, int he_t)
      {
        int go_dep = min(me, he);
        int go_t = me_t ^ he_t;
        int go_val = mul(cur[me][me_t], dp[to][he][he_t]);
        if (me < h[v] && he < h[v]) go_val = mul(go_val, inv_2);
        go[go_dep][go_t] = add(go[go_dep][go_t], go_val);
      };
      for (int me_t = 0; me_t < 2; me_t++)
      {
        for (int he = 0; he <= h[v]; he++)
        {
          for (int he_t = 0; he_t < 2; he_t++)
          {
            f(h[v], me_t, he, he_t);
          }
        }
      }
      for (int me = 0; me < h[v]; me++)
      {
        for (int me_t = 0; me_t < 2; me_t++)
        {
          for (int he_t = 0; he_t < 2; he_t++)
          {
            f(me, me_t, h[v], he_t);
          }
        }
      }
      for (int i = 0; i < h[v]; i++)
      {
        for (int t = 0; t < 2; t++)
        {
          a[i][t] = cur[i][t];
          b[i][t] = dp[to][i][t];
          c[i][t] = 0;
        }
      }
      convolution(h[v] - 1);
      for (int i = 0; i <= h[v]; i++)
      {
        for (int t = 0; t < 2; t++)
        {
          cur[i][t] = go[i][t];
          if (i < h[v])
          {
            cur[i][t] = add(cur[i][t], mul(c[i][t], inv_2));
          }
        }
      }
    }
  }
  for (int u : up[v])
  {
    for (int i = 0; i <= h[v]; i++)
    {
      for (int t = 0; t < 2; t++)
      {
        go[i][t] = cur[i][t];
      }
    }
    for (int i = 0; i <= h[v]; i++)
    {
      for (int t = 0; t < 2; t++)
      {
        int new_val = cur[i][t];
        if (i >= h[v]) new_val = mul(new_val, 2);
        go[min(i, h[u])][t ^ 1] = add(go[min(i, h[u])][t ^ 1], new_val);
      }
    }
    for (int i = 0; i <= h[v]; i++)
    {
      for (int t = 0; t < 2; t++)
      {
        cur[i][t] = go[i][t];
      }
    }
  }
  int lim = h[v];
  if (h[v] != 0)
  {
    for (int t = 0; t < 2; t++)
    {
      cur[h[v] - 1][t] = add(cur[h[v] - 1][t], mul(2, cur[h[v]][t]));
    }
    lim--;
  }
  for (int i = 0; i <= lim; i++)
  {
    for (int t = 0; t < 2; t++)
    {
      dp[v][i][t] = cur[i][t];
    }
  }
}

int main()
{
#ifdef ONPC
  freopen("a.in", "r", stdin);
#endif
  int n;
  cin >> n;
  for (int i = 1; i < n; i++)
  {
    int p;
    cin >> p;
    p--;
    g[p].push_back(i);
  }
  int q;
  cin >> q;
  while (q--)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    up[b].push_back(a);
  }
  dfs(0, -1);
  cout << add(dp[0][0][0], -dp[0][0][1]) << '\n';
}