#include <cstdio>
#include <algorithm>
#include <utility>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 5000 + 5;

int n, k, q[maxn], h[maxn];
PII a[maxn];
ll len[maxn], f[maxn], g[maxn];

ll cal(int i, int j) {
  return f[j] + (len[i] - len[j]) * h[i];
}

void dfs(int l, int r, int L, int R) {
  if (l > r) return ;
  int m = (l + r) / 2;
  int pos = -1;
  for (int i = L; i <= min(m - 1, R); i++) {
    if (pos == -1 || cal(m, i) > cal(m, pos)) {
      pos = i;
    }
  }
  g[m] = cal(m, pos);
  dfs(l, m - 1, L, pos);
  dfs(m + 1, r, pos, R);
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].second, &a[i].first);
  }
  sort(a + 1, a + 1 + n);
  int cnt = 0;
  ll all = 0;
  for (int i = 1, j = i; i <= n; i = j) {
    ll sum = 0;
    while (j <= n && a[j].first == a[i].first) {
      sum += a[j++].second;
    }
    cnt++;
    h[cnt] = a[i].first;
    len[cnt] = sum;
    all += sum * a[i].first;
  }
  n = cnt;
  if (n <= k) return puts("0"), 0;
  reverse(h + 1, h + n + 1);
  reverse(len + 1, len + n + 1);
  for (int i = 1; i <= n; i++) {
    len[i] += len[i - 1];
  }
  for (int i = 1; i <= n; i++) {
    f[i] = len[i] * h[i];
  }
  for (int i = 2; i <= k; i++) {
    dfs(1, n, 0, n);
    swap(f, g);
  }
  printf("%lld\n", all - f[n]);
  return 0;
}