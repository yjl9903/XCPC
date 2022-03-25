#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using ll = long long;
using namespace std;
const int N = 500 + 10;
const int Mod = 1e9 + 7;

struct node {
  int day, c, v, vis;
} a[N];
bool cmp(node aa, node bb) { return aa.day < bb.day; }

int d[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
ll val[20];
ll dp[N][20];
pair<int, int> G[20];

int calc(int year, int month, int day) {
  int cnt = 0, sum = 0;
  for (int i = 1; i < month; i++) sum += d[i];
  return sum + day;
}

void work() {
  int n, m, w;
  cin >> n >> m >> w;
  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;
    int year = 0, month = 0, day = 0;
    for (int i = 0; i <= 3; i++) year = year * 10 + s[i] - '0';
    for (int i = 5; i <= 6; i++) month = month * 10 + s[i] - '0';
    for (int i = 8; i <= 9; i++) day = day * 10 + s[i] - '0';
    a[i].day = calc(year, month, day);
    if (month == 2 && day == 29) {
      a[i].vis = true;
    } else {
      a[i].vis = false;
    }
    cin >> a[i].c >> a[i].v;
  }
  for (int i = 1; i <= m; i++) cin >> G[i].first >> G[i].second;
  for (int i = 0; i < (1 << m); i++) {
    int cnt = 0, Mem = 0;
    ll Val = 0;
    for (int j = 0; j < m; j++)
      if (i & (1 << j)) cnt++, Mem += G[m - j].first, Val += G[m - j].second;
    if (Mem <= w) val[cnt] = max(val[cnt], Val);
  }
  sort(a + 1, a + 1 + n, cmp);
  ll ans = 0;
  dp[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    if (a[i].vis) continue;
    for (int j = a[i].day; j >= 0; j--)
      for (int k = m; k >= 0; k--) {
        if (j >= a[i].c) dp[j][k] = max(dp[j][k], dp[j - a[i].c][k] + a[i].v);
        if (k >= 1)
          dp[j][k] = max(dp[j][k], dp[j][k - 1] - val[k - 1] + val[k]);
      }
  }
  for (int i = 0; i <= 365; i++)
    for (int j = 0; j <= m; j++) ans = max(ans, dp[i][j]), dp[i][j] = -1e9;
  cout << ans << '\n';
  for (int i = 0; i <= n; i++) a[i].day = a[i].c = a[i].v = 0;
  for (int i = 0; i <= m; i++) val[i] = 0, G[i] = {0, 0};
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    work();
  }
}