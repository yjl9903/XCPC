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

int n;
struct Node {
  int a, b, i;
} a[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i].a);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i].b);
    a[i].i = i;
  }
  sort(a + 1, a + 1 + n, [](const Node& a, const Node& b) {
    return a.a + a.b > b.a + b.b;
  });
  vector<int> va, vb;
  for (int i = 1; i <= n; i++) {
    if (i % 2 == 1) {
      va.push_back(a[i].i);
    } else {
      vb.push_back(a[i].i);
    }
  }
  for (int x: va) printf("%d ", x);
  puts("");
  for (int x: vb) printf("%d ", x);
  return 0;
}