#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#ifdef XLor
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
using namespace std;
const int N = 3000;
const int mod = 228228239;
int n;
int deep[N];
int f[N][N][2], tmp[N][2], w[N];
vector<int>g[N];
void dfs(int x) {
  deep[x] ++;
  for (auto u:g[x])
    deep[u] = deep[x], dfs(u);
}
int add(int x, int y) {
  x += y;
  if (x >= mod) x -= mod;
  return x;
}
int mul(int x, int y) {
  return 1ll * x * y % mod;
}
void dfs1(int x) {
  if (w[x]) {
    f[x][deep[x] - deep[w[x]]][0] = 1;
    f[x][deep[x] - deep[w[x]]][1] = 1;
  } else {
    f[x][0][0] = f[x][0][1] = 1;
  }
  for (auto u:g[x]){
    dfs1(u);
    int sum[2] = {0, 0}, all[2] = {0 ,0};
    for (int i = 0; i <= n; i ++)
      for (int j = 0; j < 2; j ++)
        all[j] = add(all[j], f[u][i][j]);
    for (int i = n; i >= 2; i --) {
      (sum[0] += f[x][i][0]) %= mod;
      (sum[1] += f[x][i][1]) %= mod;
      for (int j = 0; j < 2; j++)
        tmp[i - 1][j] = add(tmp[i - 1][j], mul(sum[j], f[u][i][j]));
    }
    sum[0] = sum[1] = 0;
    for (int i = n - 1; i >= 1; i --) {
      (sum[0] += f[u][i + 1][0]) %= mod;
      (sum[1] += f[u][i + 1][1]) %= mod;
      for (int j = 0; j < 2; j ++) {
        tmp[i][j] = add(tmp[i][j], mul(f[x][i][j], sum[j]));
        tmp[i][j ^ 1] = add(tmp[i][j ^ 1], mul(all[j], f[x][i][j ^ 1]));
        if (i > 0)
          tmp[i][j] = add(tmp[i][j], mul(f[u][0][j], f[x][i][j]));
        if (i > 1)
          tmp[i - 1][j] = add(tmp[i - 1][j], mul(f[x][0][j], f[u][i][j]));
      }
    }
    tmp[0][0] = add(tmp[0][0], mul(f[x][0][0], f[u][0][0]));
    tmp[0][1] = add(tmp[0][1], mul(f[x][0][1], f[u][0][1]));
    tmp[0][0] = add(tmp[0][0], mul(f[x][0][0], all[1]));
    tmp[0][1] = add(tmp[0][1], mul(f[x][0][1], all[0]));
    for (int i = 0; i <= n; i ++)
      for (int j = 0; j < 2; j ++)
        f[x][i][j] = tmp[i][j], tmp[i][j] = 0;
  }
  dbg(x);
  for (int i = 0; i <= n; i++) {
    dbg(i, f[x][i][0], f[x][i][1]);
  }
  f[x][1][0] = f[x][1][1] = 0;
}
int main() {
  scanf("%d", &n);
  for (int i = 2; i <= n; i ++) {
    int x;
    scanf("%d", &x);
    g[x].push_back(i);
  }
  dfs(1);
  int q;
  scanf("%d", &q);
  while (q -- ){
    int x, y;
    scanf("%d %d", &x, &y);
    if (!w[y] || deep[x] > deep[w[y]])
      w[y] = x;
  }
  for (int i = 1;i <= n; i ++)
    if (w[i]&& deep[w[i]] + 1 == deep[i]) {
      printf("0\n");
      return 0;
    }
  dfs1(1);
  printf("%d\n", f[1][0][1]);
  return 0;
}
