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
const int mod = 10000;
const int inf = 1 << 30;
const int maxn = 1000 + 5;

int add(int x, int y) {
  x += y; return x >= mod ? x - mod : x;
}

int n, ans;
vector<int> stk;

int dif() {
  int n = (int)stk.size() - 1;
  return abs(stk[n] - stk[n - 1]);
}

void dfs() {
  ans++;
  int d = dif();
  for (int i = 1; i < d; i++) {
    stk.push_back(i);
    dfs();
    stk.pop_back();
  }
}

int main() {
  scanf("%d", &n);
  stk.push_back(n);
  for (int i = 1; i <= n; i++) {
    stk.push_back(i);
    dfs();
    stk.pop_back();
  }
  printf("%d\n", ans % mod);
  return 0;
}