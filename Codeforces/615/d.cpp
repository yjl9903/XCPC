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
const int maxn = 400000 + 5;

int n, x, a[maxn];

int turn, cnt[maxn];
set<int> st[maxn];
void add(int x) {
  st[cnt[x]].erase(x);
  if (st[cnt[x]].empty() && cnt[x] == turn) turn++;
  cnt[x]++;
  st[cnt[x]].insert(x);
}

int main() {
  scanf("%d%d", &n, &x);
  for (int i = 0; i < x; i++) st[0].insert(i);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    add(a[i] % x);
    printf("%d\n", turn * x + *st[turn].begin());
  }
  return 0;
}