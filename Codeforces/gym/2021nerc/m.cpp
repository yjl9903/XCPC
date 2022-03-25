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
#include <unordered_map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, nn, B, vis[maxn];
vector<PII> evs[maxn];
vector<int> bag[maxn];

PII solveBig() {
  for (int i = 0; i <= nn; i++) {
    vis[i] = 0;
  }
  for (int i = 1; i <= n; i++) {
    if (bag[i].size() < B) continue;
    for (int x: bag[i]) {
      vis[x] = true;
    }
    for (int j = 1; j <= n; j++) {
      if (i == j) continue;
      int cnt = 0;
      for (int y: bag[j]) {
        cnt += vis[y];
      }
      if (cnt >= 2) {
        return { i, j };
      }
    }
    for (int x: bag[i]) {
      vis[x] = false;
    }
  }
  return { -1, -1 };
}

PII solveSmall() {
  for (int i = 0; i <= nn; i++) {
    vis[i] = 0;
    evs[i].clear();
  }
  for (int i = 1; i <= n; i++) {
    if (bag[i].size() >= B) continue;
    for (int j = 0; j < bag[i].size(); j++) {
      for (int k = 0; k < j; k++) {
        int x = bag[i][j];
        int y = bag[i][k];
        if (x > y) swap(x, y);
        evs[x].emplace_back(y, i);
      }
    }
  }
  for (int i = 1; i <= nn; i++) {
    for (auto& x: evs[i]) {
      if (vis[x.first]) {
        return { vis[x.first], x.second };
      } else {
        vis[x.first] = x.second;
      }
    }
    for (auto& x: evs[i]) {
      vis[x.first] = 0;
    }
  }
  return { -1, -1 };
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    B = 0;
    vector<int> lsh;
    for (int i = 1; i <= n; i++) {
      bag[i].clear();
      int k;
      scanf("%d", &k);
      while (k--) {
        int x;
        scanf("%d", &x);
        bag[i].push_back(x);
        lsh.push_back(x);
        B++;
      }
    }
    B = (int)sqrt(B);
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nn = lsh.size();
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j < bag[i].size(); j++) {
        bag[i][j] = lower_bound(lsh.begin(), lsh.end(), bag[i][j]) - lsh.begin() + 1;
      }
    }
    auto ans1 = solveBig();
    if (ans1.first != -1) {
      printf("%d %d\n", ans1.first, ans1.second);
    } else {
      auto ans2 = solveSmall();
      if (ans2.first != -1) {
        printf("%d %d\n", ans2.first, ans2.second);
      } else {
        puts("-1");
      }
    }
  }
  return 0;
}