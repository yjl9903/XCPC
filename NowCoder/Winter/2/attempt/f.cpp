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
  auto cmpA = [](const Node& a, const Node& b) {
    // if (a.a - a.b != b.a - b.b) {
    //   return a.a - a.b > b.a - b.b;
    // }
    if (a.a != b.a) {
      return a.a > b.a;
    } else if (a.b != b.b) {
      return a.b > b.b;
    } else {
      return a.i < b.i;
    }
  };
  auto cmpB = [](const Node& a, const Node& b) {
    // if (a.b - a.a != b.b - b.a) {
    //   return a.b - a.a > b.b - b.a;
    // }
    if (a.b != b.b) {
      return a.b > b.b;
    } else if (a.a != b.a) {
      return a.a > b.a;
    } else {
      return a.i > b.i;
    }
  };
  multiset<Node, decltype(cmpA)> sta(cmpA);
  multiset<Node, decltype(cmpB)> stb(cmpB);
  for (int i = 1; i <= n; i++) {
    sta.insert(a[i]);
    stb.insert(a[i]);
  }
  vector<int> va, vb;
  for (int i = 1; i <= n; i++) {
    if (i % 2 == 1) {
      auto x = *sta.begin();
      va.push_back(x.i);
      sta.erase(sta.find(x));
      stb.erase(stb.find(x));
    } else {
      auto x = *stb.begin();
      vb.push_back(x.i);
      sta.erase(sta.find(x));
      stb.erase(stb.find(x));
    }
  }
  for (int x: va) printf("%d ", x);
  puts("");
  for (int x: vb) printf("%d ", x);
  return 0;
}