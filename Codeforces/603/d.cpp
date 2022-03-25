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

int n, pre[maxn], siz[maxn];
char s[100];

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
  x = find(x); y = find(y);
  if (x == y) return ;
  pre[x] = y; siz[y] += siz[x];
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n + 27; i++) {
    pre[i] = i; siz[i] = 1;
    if (i > n) siz[i]--;
  }
  for (int i = 1; i <= n; i++) {
    scanf("%s", s);
    for (int j = 0; s[j]; j++) {
      join(i, n + 1 + s[j] - 'a');
    }
  }
  int ans = 0;
  for (int i = 1; i <= n + 27; i++) {
    if (i == find(i) && siz[find(i)]) {
      ans++;
    }
  }
  cout << ans;
  return 0;
}