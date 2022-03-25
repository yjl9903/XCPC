#include <cstdio>
using namespace std;
const int maxn = 1000000 + 5;

int n, q;

unsigned long long a[maxn];

const unsigned long long u[5] = {
  314882150829468584,
  427197303358170108,
  1022292690726729920,
  1698479428772363217,
  2006101093849356424
};

const unsigned long long p = 2009731336725594113;

int func(unsigned long long x) {
  return x % p % 2019;
}

unsigned long long qmul(unsigned long long x, unsigned long long y) {
  unsigned long long r = 0;
  while (y) {
    if (y % 2) r = (r + x) % p;
    x = (x + x) % p; y /= 2;
  }
  return r;
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    a[i] = i;
  }
  for (int i = 1; i <= q; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    unsigned long long s = 0;
    for (int i = l; i <= r; i++) {
      s += func(a[i]);
    }
    printf("%llu\n", s);
    for (int i = l; i <= r; i++) {
      a[i] = qmul(a[i], u[s % 5]);
    }
  }
  return 0;
}