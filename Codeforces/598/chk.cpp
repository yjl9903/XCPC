#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, a[maxn], ans[maxn], mx[maxn], mn[maxn], cnt[maxn];

int main() {
  FILE* in = fopen("../input/in.txt", "r");
  FILE* out = fopen("../input/out.txt", "r");
  fscanf(in, "%d", &n);
  for (int i = 1; i <= n; i++) fscanf(in, "%d", a + i);
  ll ans; int k;
  fscanf(out, "%lld%d", &ans, &k);
  for (int i = 1; i <= k; i++) mx[i] = 0, mn[i] = inf;
  for (int i = 1, x; i <= n; i++) {
    fscanf(out, "%d", &x);
    mx[x] = max(mx[x], a[i]);
    mn[x] = min(mn[x], a[i]);
    cnt[x]++;
  }
  ll tot = 0;
  for (int i = 1; i <= k; i++) {
    tot += mx[i] - mn[i];
    if (mx[i] == 0 || mn[i] == inf) {
      printf("Error: %d\n", i);
    }
    if (cnt[i] < 3) {
      printf("Error: %d\n", i);
    }
  }
  cout << ans << " : " << tot << endl;
  return 0;
}