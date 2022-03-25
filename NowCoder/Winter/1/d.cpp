#include <cstdio>
using namespace std;
const int maxn = 1e5 + 5;

int n, a[maxn], vis[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i); vis[a[i]] = true;
  }
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      printf("%d", i);
    }
  }
  return 0;
}