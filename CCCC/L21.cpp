#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9 + 7;
const int maxn = 1000 + 5;

int n, a[maxn];
char op[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 1; i < n; i++) {
    char tmp[4];
    scanf("%s", tmp);
    op[i] = tmp[0];
  }
  int flag = inf;
  for (int i = n - 1; i >= 1; i--) {
    int x = a[i], y = a[i + 1];
    if (op[i] == '+') {
      a[i] = x + y;
    } else if (op[i] == '-') {
      a[i] = x - y;
    } else if (op[i] == '*') {
      a[i] = x * y;
    } else if (op[i] == '/') {
      if (y == 0) {
        flag = x;
        break;
      }
      a[i] = x / y;
    }
  }
  if (flag != inf) {
    printf("ERROR: %d/0\n", flag);
  } else {
    printf("%d\n", a[1]);
  }
  return 0;
}