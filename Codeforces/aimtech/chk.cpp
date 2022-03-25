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
const int maxn = 100000 + 5;

int n = 10, tag = 214;

vector<int> stk;
void dfs(int u, int mn, int sum) {
  if (u == n + 1) {
    if (sum != tag) return ;
    for (int x: stk) cout << x << ' ';
    cout << endl;
    return ;
  }
  if (sum > tag) return ;
  for (int i = mn; i <= n; i++) {
    stk.push_back(i);
    dfs(u + 1, i, sum + i * i);
    stk.pop_back();
  }
}

int main() {
  dfs(1, 1, 0);
  return 0;
}