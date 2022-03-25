#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int, int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;
const double pi = acos(-1.0);

struct complex {
  double x, y;
  complex(double a = 0, double b = 0) : x(a), y(b) {}
  complex operator+(const complex& b) { return complex{x + b.x, y + b.y}; }
  complex operator-(const complex& b) { return complex{x - b.x, y - b.y}; }
  complex operator*(const complex& b) {
    return complex{x * b.x - y * b.y, x * b.y + y * b.x};
  }
} a[maxn], b[maxn];
int rev[maxn];
void fft(int n, complex a[], int op = 1) {
  for (int i = 0; i < n; i++)
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int i = 1; i < n; i <<= 1) {
    complex t(cos(pi / i), op * sin(pi / i));
    for (int j = 0; j < n; j += (i << 1)) {
      complex w(1, 0);
      for (int k = 0; k < i; k++, w = w * t) {
        complex x = a[j + k], y = w * a[j + k + i];
        a[j + k] = x + y;
        a[j + k + i] = x - y;
      }
    }
  }
  if (op == -1)
    for (int i = 0; i < n; i++) a[i].x /= n, a[i].y /= n;
}
void mul(int n, complex a[], int m, complex b[], int ans[]) {
  int l = 0, lim = 1;
  while (lim <= n + m) l++, lim <<= 1;
  for (int i = 0; i < lim; i++)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
  fft(lim, a);
  fft(lim, b);
  for (int i = 0; i <= lim; i++) a[i] = a[i] * b[i];
  fft(lim, a, -1);
  for (int i = 0; i <= n + m; i++) ans[i] = (int)(a[i].x + 0.5);
}

int n1, n2, n3, ans[maxn], a2[maxn];

int main() {
  scanf("%d", &n1);
  for (int i = 1; i <= n1; i++) {
    int x;
    scanf("%d", &x);
    a[x + 30000].x = a[x + 30000].x + 1;
  }
  scanf("%d", &n2);
  for (int i = 1; i <= n2; i++) {
    scanf("%d", a2 + i);
  }
  scanf("%d", &n3);
  for (int i = 1; i <= n3; i++) {
    int x;
    scanf("%d", &x);
    b[x + 30000].x = b[x + 30000].x + 1;
  }
  mul(30000 * 2 + 5, a, 30000 * 2 + 5, b, ans);
  ll res = 0;
  for (int i = 1; i <= n2; i++) {
    int x = a2[i];
    res += ans[x + x + 60000];
  }
  printf("%lld\n", res);
  return 0;
}