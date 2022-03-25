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
const int maxn = 200000 + 5;

int n, r;

int dis(PII x, PII y) {
  int dx = x.first - y.first;
  int dy = x.second - y.second;
  return dx * dx + dy * dy;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &r);
    vector<PII> key;
    for (int i = -r; i <= r; i++) {
      for (int j = -r; j <= r; j++) {
        if (i * i + j * j <= r * r) {
          key.push_back({ i, j });
        }
      }
    }
    int ans = 0;
    vector< vector<PII> > plan;
    for (int i = 0; i < key.size(); i++) {
      for (int j = i; j < key.size(); j++) {
        for (int k = j; k < key.size(); k++) {
          int tot = dis(key[i], key[j]) + dis(key[i], key[k]) + dis(key[j], key[k]);
          if (tot > ans) {
            ans = tot;
            plan = { { key[i], key[j], key[k] } };
          } else if (tot == ans) {
            plan.push_back({ key[i], key[j], key[k] });
          }
        }
      }
    }
    cout << ans << endl;
    for (auto& v: plan) {
      printf("(%d, %d) ", v[0].first, v[0].second);
      printf("(%d, %d) ", v[1].first, v[1].second);
      printf("(%d, %d)\n", v[2].first, v[2].second);
    }
  }
  return 0;
}