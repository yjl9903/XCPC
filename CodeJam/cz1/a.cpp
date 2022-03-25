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
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, k, a[30][30], c[maxn], id[maxn], b[30];

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    char op[3];
    scanf("%d%s", c + i, op);
    id[i] = op[0] - 'A' + 1;
  }
  for (int i = 1; i <= k; i++) {
    for (int j = 1; j <= k; j++) {
      scanf("%d", &a[i][j]);
    }
  }
  for (int i = 1; i <= k; i++) {
    int sum = 0;
    for (int j = 1; j <= k; j++) {
      sum += a[j][i];
    }
    int rest = 0, cnt = 0;
    for (int j = 1; j <= k; j++) {
      if (abs(sum - k * a[j][i]) <= 15 * k) {
        rest += a[j][i];
        cnt++;
      }
    }
    b[i] = rest / cnt;
    if (rest % cnt >= (cnt + 1) / 2) b[i]++;
  }
  vector<PII> vec;
  for (int i = 1; i <= n; i++) {
    int sum = (6 * c[i] + 4 * b[id[i]]);
    if (sum % 10 < 5) {
      sum /= 10;
    } else {
      sum /= 10; sum++;
    }
    vec.emplace_back(sum, -id[i]);
  }
  sort(begin(vec), end(vec), greater<PII>());
  for (int i = 0; i < n; i++) {
    printf("%d %c\n", vec[i].first, -vec[i].second - 1 + 'A');
  }
  return 0;
}