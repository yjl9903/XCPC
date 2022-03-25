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
const int maxn = 1000000 + 5;

int n, a[maxn], cnt[maxn];
bool sk[maxn];
vector<int> divs[maxn];

void ban(int pos) {
  for (int i = 1; i <= n; i++) {
    if (i == pos) continue;
    int val = abs(a[i] - a[pos]);
    for (int x: divs[val]) sk[x] = true;
  }
}

int main() {
  scanf("%d", &n);
  if (n == 1) {
    puts("1");
    return 0;
  }
  for (int i = n - 1; i < maxn && i <= n + n + n; i++) {
    for (int j = i; j < maxn && j <= n + n + n; j += i) {
      divs[j].push_back(i);
    }
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  sort(a + 1, a + 1 + n);
  for (int i = 1; i <= 50 && i <= n; i++) {
    ban(i);
    ban(n - i + 1);
  }
  for (int i = n - 1;; i++) {
    if (sk[i]) continue;
    bool flag = true;
    for (int j = 1; j <= n; j++) {
      cnt[a[j] % i]++;
      if (cnt[a[j] % i] > 1) {
        flag = false;
        while (j >= 1) {
          cnt[a[j] % i]--;
          j--;
        }
        break;
      }
    }
    if (flag) {
      printf("%d\n", i);
      break;
    }
  }
  return 0;
}