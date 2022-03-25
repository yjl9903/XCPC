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

int main() {
  scanf("%d", &n);
  vector<PII> vec;
  vec.push_back({ 1, 1 });
  vec.push_back({ 0, 1 });
  vec.push_back({ 0, 0 });
  vec.push_back({ 1, 0 });
  for (int i = 1; i <= n; i++) {
    vec.push_back({ i + 1, i + 1 });
    vec.push_back({ i, i + 1 });
    vec.push_back({ i + 1, i });
  }
  printf("%d\n", vec.size());
  for (auto& x: vec) {
    printf("%d %d\n", x.first, x.second);
  }
  return 0;
}