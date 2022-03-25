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

typedef unsigned long long ull;
const int seed = 135;
const int p1 = 999999937, p2 = 19260817;
ull xp1[maxn], xp2[maxn], xp[maxn];

struct Hash {
  static void init() {
    xp1[0] = xp2[0] = xp[0] = 1;
    for (int i = 1; i < maxn; ++i) {
      xp1[i] = xp1[i - 1] * seed % p1;
      xp2[i] = xp2[i - 1] * seed % p2;
      xp[i] = xp[i - 1] * seed;
    }
  }

  ull h[maxn];
  ull build(int n, const char* s) {
    ull r1 = 0, r2 = 0;
    for (int i = 1; i <= n; i++) {
      r1 = (r1 * seed + s[i]) % p1;
      r2 = (r2 * seed + s[i]) % p2;
      h[i] = (r1 << 32) | r2;
    }
    return h[n];
  }

  ull query(int l, int r) {
    int len = r - l + 1;
    unsigned int mask32 = ~(0u);
    ull left1 = h[l - 1] >> 32, right1 = h[r] >> 32;
    ull left2 = h[l - 1] & mask32, right2 = h[r] & mask32;
    return (((right1 - left1 * xp1[len] % p1 + p1) % p1) << 32) |
        (((right2 - left2 * xp2[len] % p2 + p2) % p2));
  }
} h;

int n, k;
char s[maxn];

int check(int l) {
  map<ull,vector<int> > mp;
  for (int i = 1; i + l - 1 <= n; i++) {
    mp[h.query(i, i + l - 1)].push_back(i);
  }
  for (auto& x: mp) {
    if (x.second.size() < k) continue;
    int last = 0, cnt = 0;
    for (int s: x.second) {
      if (s > last) {
        cnt++;
        last = s + l - 1;
        if (cnt == k) return true;
      }
    }
  }
  return false;
}

int main() {
  Hash::init();
  scanf("%d%d%s", &n, &k, s + 1);
  h.build(n, s);
  int ans = 0, l = 0, r = n;
  while (l <= r) {
    int m = (l + r) / 2;
    if (check(m)) {
      ans = m; l = m + 1;
    } else {
      r = m - 1;
    }
  }
  printf("%d\n", ans);
  return 0;
}