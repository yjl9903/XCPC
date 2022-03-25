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

int sum;
int L[] = {
  0, 60, 62, 65, 67, 70, 75, 80, 85, 90, 95
};
double score[] = {
  0, 1, 1.7, 2.0, 2.3, 2.7, 3.0, 3.3, 3.7, 4.0, 4.3
};

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &sum);
    double ans = 0;
    for (int i = 0; i <= 10; i++) {
      for (int j = i; j <= 10; j++) {
        for (int p = j; p <= 10; p++) {
          for (int q = p; q <= 10; q++) {
            if (sum >= L[i] + L[j] + L[p] + L[q]) {
              ans = max(ans, score[i] + score[j] + score[p] + score[q]);
            }
          }
        }
      }
    }
    printf("%.1lf\n", ans);
  }
  return 0;
}