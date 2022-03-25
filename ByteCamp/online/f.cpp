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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

int n, a[maxn];
vector<int> bag[10];

int out(const vector<int>& v) {
  printf("%d\n", (int)v.size());
  for (auto x: v) printf("%d ", x);
  return 0;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }

  sort(a + 1, a + 1 + n, greater<int>());
  for (int i = 1; i + n / 3 - 1 <= n; i++) {
    if (a[i] < a[i + n / 3 - 1] * 2) {
      printf("%d\n", n / 3);
      for (int j = 0; j < n / 3; j++) {
        printf("%d ", a[i + j]);
      }
      return 0;
    }
  }
  
  for (int i = 1; i <= n; i++) bag[a[i] % 2].push_back(a[i]);
  if ((int)bag[1].size() >= n / 3) {
    return out(bag[1]);
  }

  bag[0].clear(); bag[1].clear();
  for (int i = 1; i <= n; i++) bag[a[i] % 3].push_back(a[i]);
  if ((int)bag[1].size() >= n / 3) {
    return out(bag[1]);
  } else if ((int)bag[2].size() >= n / 3) {
    return out(bag[2]);
  }

  bag[0].clear(); bag[1].clear(); bag[2].clear();
  for (int i = 1; i <= n; i++) bag[a[i] % 4].push_back(a[i]);
  if ((int)bag[1].size() + (int)bag[3].size() >= n / 3) {
    vector<int> v(bag[1]);
    for (auto x: bag[3]) v.push_back(x);
    return out(v);
  } else if ((int)bag[2].size() >= n / 3) {
    return out(bag[2]);
  }

  bag[0].clear(); bag[1].clear(); bag[2].clear(); bag[3].clear();
  for (int i = 1; i <= n; i++) bag[a[i] % 5].push_back(a[i]);
  if ((int)bag[1].size() + (int)bag[4].size() >= n / 3) {
    vector<int> v(bag[1]);
    for (auto x: bag[4]) v.push_back(x);
    return out(v);
  } else if ((int)bag[2].size() + (int)bag[3].size() >= n / 3) {
    vector<int> v(bag[2]);
    for (auto x: bag[3]) v.push_back(x);
    return out(v);
  }

  assert(0);
  return 0;
}