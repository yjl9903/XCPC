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

int n, m;
char s[maxn];

int main() {
  scanf("%d", &m);
  map<string,vector<PII> > mp;
  for (int i = 1, k; i <= m; i++) {
    scanf("%d", &k);
    for (int j = 1; j <= k; j++) {
      scanf("%s", s);
      mp[s].push_back({ i, j });
    }
  }
  map<string,int> poi;
  for (auto& x: mp) {
    poi[x.first] = 0;
  }
  scanf("%d", &n);
  vector<PII> ans;
  bool flag = true;
  for (int i = 1; i <= n; i++) {
    scanf("%s", s);
    if (mp.count(s)) {
      ans.push_back(mp[s][poi[s]]);
      poi[s]++;
      if (poi[s] == (int)mp[s].size()) {
        poi[s] = 0;
      }
    } else {
      flag = false;
    }
  }
  if (flag) {
    for (auto& x: ans) {
      printf("%d %d\n", x.first, x.second);
    }
  } else {
    puts("NOT POSSIBLE");
  }
  return 0;
}