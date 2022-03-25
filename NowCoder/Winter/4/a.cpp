#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

long long fib[100];

int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

int main() {
  int T; scanf("%d", &T);
  fib[0] = 1; fib[1] = 1;
  for (int i = 2; i <= 80; i++) {
    fib[i] = fib[i - 1] + fib[i - 2];
  }
  while (T--) {
    int n; scanf("%d", &n);
    if (n == 0) {
      puts("1"); continue;
    }
    // gcd(fib[n + 1], fib[n]);
    printf("%lld\n", fib[n + 1] + fib[n]);
  }
  return 0;
}