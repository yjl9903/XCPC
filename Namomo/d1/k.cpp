#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#ifdef XLor
#define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
void err() { std::cout << "\033[39;0m" << std::endl; }
template <typename T, typename... Args>
void err(T a, Args... args) {
  std::cout << a << ' ';
  err(args...);
}
#else
#define dbg(...)
#endif
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int, int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 2000 + 5;

int n, m;
vector<int> G[maxn];
bitset<105> a[maxn];

namespace Gauss {
  int piv[maxn], fre[maxn], tot;

  template<int N>
  int solve(bitset<N> A[], int n, int m) {
    int r = 0;
    tot = 0;
    for (int c = 0; c < m && r < n; c++, r++) {
      int mx = r;
      for (int i = r; i < n; i++) {
        if (A[i][c]) {
          mx = i;
          break;
        }
      }
      if (!A[mx][c]) {
        r--;
        fre[tot++] = c;
        continue;
      }
      piv[r] = c;
      swap(A[r], A[mx]);
      for (int i = 0; i < n; ++i) {
        if (i == r || !A[i][c]) continue;
        A[i] ^= A[r];
      }
    }
    for (int i = r; i < n; i++)
      if (A[i][m]) return -1;
    return r;
  }
}  // namespace Gauss

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--;
    v--;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  for (int i = 0; i < n; i++) {
    if (G[i].size() % 2 == 0) {
      a[i].set(n);
      for (int v : G[i]) {
        a[i].set(v);
      }
    } else {
      a[i].set(i);
      for (int v : G[i]) {
        a[i].set(v);
      }
    }
  }
  int rank = Gauss::solve<105>(a, n, n);
  if (rank == -1) puts("N");
  else puts("Y");
  return 0;
}