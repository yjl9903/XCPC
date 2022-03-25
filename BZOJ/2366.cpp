#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 1000000;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

void add(int& x, int y) {
  x += y; if (x >= mod) x -= mod;
}

namespace acam {
  static const int maxp = 100000 + 5;
  static const int S = 26;
  int sz, ch[maxp][S], fail[maxp], match[maxp];
  int node() {
    ms(ch[++sz], 0); fail[sz] = 0;
    return sz;
  }
  void clear() {
    sz = 0; node();
    for (int i = 0; i < S; i++) ch[0][i] = 1;
  }
  int insert(char* s, int i) {
    int u = 1;
    for (int i = 0; s[i]; i++) {
      int v = s[i] - 'a'; // !
      if (!ch[u][v]) ch[u][v] = node();
      u = ch[u][v];
    }
    match[u] = i;
    return u;
  }
  void build() {
    queue<int> q; q.push(1);
    while (!q.empty()) {
      int t = q.front(); q.pop();
      for (int i = 0; i < S; i++) {
        if (ch[t][i]) {
          fail[ch[t][i]] = ch[fail[t]][i];
          if (match[fail[ch[t][i]]]) {
            match[ch[t][i]] = match[fail[ch[t][i]]];
          }
          q.push(ch[t][i]);
        } else {
          ch[t][i] = ch[fail[t]][i];
        }
      }
    }
  }
}

int n, m, len[maxn], dp[2][maxn];
char s[maxn];
vector<int> bag[maxn];

int main() {
  acam::clear();
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s);
    acam::insert(s, i);
    len[i] = strlen(s);
  }
  acam::build();
  scanf("%s", s + 1);
  m = strlen(s + 1);
  for (int i = 1, u = 1; i <= m; i++) {
    u = acam::ch[u][s[i] - 'a'];
    if (acam::match[u]) bag[acam::match[u]].push_back(i);
  }
  int f = 0;
  for (int i = 0; i < (int)bag[1].size(); i++) dp[f][i] = 1;
  for (int i = 2; i <= n; i++, f ^= 1) {
    int sum = 0, p = 0;
    for (int j = 0; j < (int)bag[i].size(); j++) {
      while (p < (int)bag[i - 1].size() && bag[i - 1][p] + len[i] <= bag[i][j]) {
        add(sum, dp[f][p]); p++;
      }
      dp[f ^ 1][j] = sum;
    }
  }
  int ans = 0;
  for (int i = 0; i < (int)bag[n].size(); i++) add(ans, dp[f][i]);
  printf("%d\n", ans);
  return 0;
}