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

int n;
ll a[maxn];
char s[maxn];

void parse(vector<ll>& lsh) {
  sort(begin(lsh), end(lsh));
  lsh.resize(unique(begin(lsh), end(lsh)) - begin(lsh));
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%s", &n, s + 1);
    vector<ll> lsh = { 0 };
    auto gid = [&lsh](ll x) {
      return lower_bound(begin(lsh), end(lsh), x) - begin(lsh) + 1;
    };
    for (int i = 1; i < n; i++) {
      if (s[i] == '<') {
        a[i + 1] = a[i] + 1;
      } else {
        a[i + 1] = a[i] - maxn;
      }
      lsh.push_back(a[i + 1]);
    }
    parse(lsh);
    for (int i = 1; i <= n; i++) {
      printf("%d%c", gid(a[i]), " \n"[i == n]);
    }
    lsh.assign(1, 0);
    for (int i = 1; i < n; i++) {
      if (s[i] == '<') {
        a[i + 1] = a[i] + maxn;
      } else {
        a[i + 1] = a[i] - 1;
      }
      lsh.push_back(a[i + 1]);
    }
    parse(lsh);
    for (int i = 1; i <= n; i++) {
      printf("%d%c", gid(a[i]), " \n"[i == n]);
    }
  }
  return 0;
}