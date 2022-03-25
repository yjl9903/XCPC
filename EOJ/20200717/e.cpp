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

int k;
ll pri[maxn];
int cnt[maxn], dirs[maxn];

int main() {
  scanf("%d", &k);
  map<ll, int> mp;
  for (int i = 1; i <= k; i++) {
    ll p; int k;
    scanf("%lld%d", &p, &k);
    mp[p] += k;
  }
  int i = 0;
  for (auto& x: mp) {
    pri[i] = x.first;
    cnt[i] = x.second;
    dirs[i] = 1;
    i++;
  }
  function<void(ll&,int,bool)> dfs = [&](ll& tot, int pos, bool dir) {
    if (pos == 0) {
      for (int i = 0; i < cnt[pos]; i++) {
        if (dirs[pos]) {
          printf("%lld\n", tot *= pri[pos]);
        } else {
          assert(tot % pri[pos] == 0);
          printf("%lld\n", tot /= pri[pos]);
        }
      }
      dirs[pos] ^= 1;
      return ;
    }

    bool f = dir;
    dfs(tot, pos - 1, f);
    for (int i = 0; i < cnt[pos]; i++) {
      if (dirs[pos]) {
        tot *= pri[pos];
      } else {
        assert(tot % pri[pos] == 0);
        tot /= pri[pos];
      }
      printf("%lld\n", tot);
      dfs(tot, pos - 1, f ^= 1);
    }
    dirs[pos] ^= 1;
  };
  puts("1");
  ll tot = 1;
  dfs(tot, i - 1, 1);
  return 0;
}