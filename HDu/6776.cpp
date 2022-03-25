#include <cstdio>
#include <vector>
#include <algorithm>

int n, a[100001];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
      scanf("%d", a + i);
    }
    std::sort(a, a + n);
    std::vector<long long> v;
    // printf("%u\n", v.size() - 1);
    for (int i = 0; i < v.size() - 1ll; i++) {
      puts("H");
    }
    for (int i = 1; i < n; i++) {
      v.push_back(a[i] - a[i - 1]);
    }
    long long sum = 0;
    for (int i = 0; i < n - 1; i++) {
      sum += (i + 1) * (n - 1 - i) * v[i];
    }
    if (n == 1) {
      sum = 0;
    }
    printf("%lld\n", sum);
  }
  return 0;
}