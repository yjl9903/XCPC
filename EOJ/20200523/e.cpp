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
const int maxn = 500000 + 5;

int n, m;
set<int> edge[maxn];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].insert(v);
    edge[v].insert(u);
  }
  
  return 0;
}