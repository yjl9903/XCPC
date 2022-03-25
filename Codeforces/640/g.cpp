#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, a[maxn];
const int plan[] = {
  2, 5, 1, 3, 7, 4, 6, 8
};

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    if (n <= 3) {
      puts("-1");
    } else if (n == 4) {
      puts("3 1 4 2");
    } else if (n == 5) {
      puts("3 1 4 2 5");
    } else if (n == 6) {
      puts("3 1 4 6 2 5");
    } else if (n == 7) {
      puts("3 1 4 6 2 5 7");
    } else {
      for (int i = 0; i + 7 < n; i += 8) {
        for (int j = i; j < n && j < i + 8; j++) {
          a[j] = i + plan[j - i];
        }
      }
      if (n % 8 == 1) {
        a[n - 1] = n;
        swap(a[n - 2], a[n - 3]);
      } else if (n % 8 == 2) {
        a[n - 1] = n - 1;
        a[n - 2] = n - 4;
        a[n - 3] = n;
        a[n - 4] = n - 2;
      } else if (n % 8 == 3) {
        a[n - 1] = n;
        a[n - 2] = n - 2;
        a[n - 3] = n - 5;
        a[n - 4] = n - 1;
        a[n - 5] = n - 3;
      } else if (n % 8 == 4) {
        a[n - 1] = n - 1;
        a[n - 2] = n - 3;
        a[n - 3] = n - 6;
        a[n - 4] = n - 2;
        a[n - 5] = n;
        a[n - 6] = n - 4;
      } else if (n % 8 == 5) {
        a[n - 1] = n;
        a[n - 2] = n - 2;
        a[n - 3] = n - 4;
        a[n - 4] = n - 7;
        a[n - 5] = n - 3;
        a[n - 6] = n - 1;
        a[n - 7] = n - 5;
      } else if (n % 8 == 6) {
        a[n - 1] = n - 1;
        a[n - 2] = n - 3;
        a[n - 3] = n - 5;
        a[n - 4] = n - 8;
        a[n - 5] = n - 4;
        a[n - 6] = n;
        a[n - 7] = n - 2;
        a[n - 8] = n - 6;
      } else if (n % 8 == 7) {
        a[n - 1] = n - 2;
        a[n - 2] = n;
        a[n - 3] = n - 4;
        a[n - 4] = n - 6;
        a[n - 5] = n - 9;
        a[n - 6] = n - 5;
        a[n - 7] = n - 1;
        a[n - 8] = n - 3;
        a[n - 9] = n - 7;
      }
      for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
      }
      puts("");
    }
  }
  return 0;
}