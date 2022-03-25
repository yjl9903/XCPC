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
const int S = 61;
const int maxn = 1000000 + 5;

int n, k, L[maxn], R[maxn];
int cnt[maxn], cov[maxn];
int ord[maxn], pre[maxn], nxt[maxn];
bool bad[maxn];
ll val[maxn], id[maxn];

int bit(ll x, int i) {
  return x >> i & 1;
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= k; i++) {
    scanf("%d%d%lld", L + i, R + i, val + i);
  }
  for (int b = 0; b < S; b++) {
    ms(cnt, 0);
    ms(id, 0);
    ms(cov, 0);
    ms(ord, -1);
    for (int i = 1; i <= k; i++) {
      if (bit(val[i], b) == 1) {
        cnt[L[i]]++;
        cnt[R[i] + 1]--;
        id[L[i]] += i;
        id[R[i] + 1] -= i;
      }
    }
    for (int i = 1; i <= n; i++) {
      cnt[i] += cnt[i - 1];
      id[i] += id[i - 1];
      cov[i] = cov[i - 1];
      if (cnt[i] > 0) {
        cov[i]++;
      }
    }
    int zeroId = -1;
    for (int i = 1; i <= k; i++) {
      if (bit(val[i], b) == 0) {
        if (cov[R[i]] - cov[L[i] - 1] == R[i] - L[i] + 1) {
          if (zeroId == -1) {
            zeroId = i;
          } else if (zeroId > 0) {
            zeroId = -2;
          }
        }
      }
    }
    if (zeroId == -1) continue;
    for (int i = 1; i <= k; i++) {
      if (bit(val[i], b) == 0) {
        if (i != zeroId) bad[i] = true;
      }
    }
    int tot = 0, last = -1;
    for (int i = 1; i <= n; i++) {
      if (cnt[i] == 1) {
        if (id[i] != last) {
          ord[id[i]] = ++tot;
          last = id[i];
        }
      }
    }
    pre[0] = 0;
    for (int i = 1; i <= n; i++) {
      pre[i] = pre[i - 1];
      if (cnt[i] == 1) pre[i] = i;
    }
    nxt[n + 1] = n + 1;
    for (int i = n; i >= 1; i--) {
      nxt[i] = nxt[i + 1];
      if (cnt[i] == 1) nxt[i] = i;
    }
    bool all = false;
    int ll = 1, rr = tot;
    for (int i = 1; i <= k; i++) {
      if (bit(val[i], b) == 0) {
        if (cov[R[i]] - cov[L[i] - 1] == R[i] - L[i] + 1) {
          int l = nxt[L[i]];
          int r = pre[R[i]];
          if (l > r) {
            all = true;
            break;
          }
          ll = max(ll, ord[id[l]]);
          rr = min(rr, ord[id[r]]);
        }
      }
    }
    if (all || ll > rr) {
      for (int i = 1; i <= k; i++) {
        if (bit(val[i], b) == 1) {
          bad[i] = true;
        }
      }
    } else {
      for (int i = 1; i <= k; i++) {
        if (bit(val[i], b) == 1) {
          int x = ord[i];
          if (x < ll || x > rr) {
            bad[i] = true;
          }
        }
      }
    }
  }
  for (int i = 1; i <= k; i++) {
    putchar(bad[i] ? '0' : '1');
  }
  return 0;
}