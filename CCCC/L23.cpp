#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;

int n, a[maxn];

map<int,int> ch[2];

void solve(int l, int r) {
  // cout << l << ' ' << r << endl;
  if (l > r) return ;
  // printf("%d ", a[r]);
  int k = 1;
  while ((1 << k) - 1 <= r - l + 1) k++;
  k--;
  int rest = (r - l + 1) - ((1 << k) - 1);
  int Lsz = (1 << (k - 1)) - 1 + min(rest, 1 << (k - 1));
  if (Lsz > 0) {
    ch[0][a[r]] = a[l + Lsz - 1];
    solve(l, l + Lsz - 1);
  }
  if (Lsz + 1 < r - l + 1) {
    ch[1][a[r]] = a[r - 1];
    solve(l + Lsz, r - 1);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  solve(1, n);
  queue<int> q;
  q.push(a[n]);
  int tot = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    tot++;
    printf("%d%c", u, tot == n ? '\n' : ' ');
    if (ch[0].count(u)) {
      q.push(ch[0][u]);
    }
    if (ch[1].count(u)) {
      q.push(ch[1][u]);
    }
  }
  return 0;
}