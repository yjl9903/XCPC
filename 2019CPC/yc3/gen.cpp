#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  int n = atoi(argv[1]);
  printf("%d %d\n", n, n);
  for (int i = 1; i <= n; i++) {
    if (i > 1) putchar(' ');
    printf("%d", rnd.next((int)1e9) + 1);
  }
  puts("");
  for (int i = 0; i < n - 1; i++) {
    if (i) putchar(' ');
    printf("%d", 1 + rnd.next(i + 1));
  }
  return 0;
}