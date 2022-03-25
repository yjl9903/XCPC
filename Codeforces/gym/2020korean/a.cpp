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
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const ll inf = 1ll << 61;
const int maxn = 500000 + 5;

ll mul(ll x, ll y) {
  if (1.0 * x * y >= inf) return inf;
  return x * y;
}
ll add(ll x, ll y) {
  if (x + y >= inf) return inf;
  return x + y;
}

struct Event {
  ll k;
  int id, pos;

  bool operator < (const Event& rhs) const {
    return k < rhs.k;
  }
} ev[maxn];

char m0[maxn], s[maxn];
int mlen, slen, k, q, pre[maxn];
int sum, tot = 1;
ll len[maxn];
string ans[maxn];

void dfs(int k, ll base) {
  if (k == 0) {
    // dbg(k, base);
    while (tot <= sum && ev[tot].k <= add(base, mlen)) {
      ans[ev[tot].id][ev[tot].pos] = m0[ev[tot].k - base];
      // dbg(ev[tot].k - base, m0[ev[tot].k - base]);
      tot++;
    }
  } else {
    auto cal = [&](int i) {
      if (i == 0) return 0ll;
      return add(mul(len[k - 1], pre[i]), i - pre[i]);
    };
    auto find = [&](ll k) {
      int l = 1, r = slen, ans = -1;
      while (l <= r) {
        int m = (l + r) / 2;
        if (add(cal(m), base) >= k) {
          ans = m;
          r = m - 1;
        } else {
          l = m + 1;
        }
      }
      assert(ans != -1);
      return ans;
    };
    while (tot <= sum && ev[tot].k <= add(base, len[k])) {
      int pos = find(ev[tot].k);
      if (s[pos] == '$') {
        // dfs in
        dfs(k - 1, add(base, cal(pos - 1)));
      } else {
        ans[ev[tot].id][ev[tot].pos] = s[pos];
        tot++;
      }
    }
  }
}

int main() {
  scanf("%s%s", m0 + 1, s + 1);
  scanf("%d%d", &k, &q);
  mlen = strlen(m0 + 1);
  slen = strlen(s + 1);
  dbg(m0 + 1);
  int scnt = 0;
  for (int i = 1; i <= slen; i++) {
    pre[i] = pre[i - 1];
    if (s[i] == '$') {
      scnt++;
      pre[i]++;
    }
  }
  len[0] = mlen;
  for (int i = 1; i <= k; i++) {
    len[i] = add(mul(scnt, len[i - 1]), slen - scnt);
  }
  for (int cas = 1; cas <= q; cas++) {
    ll a, b;
    scanf("%lld%lld", &a, &b);
    for (ll i = a; i <= b; i++) {
      ev[++sum] = Event { i, cas, int(i - a) };
      ans[cas] += ' ';
    }
  }
  sort(ev + 1, ev + sum + 1);
  dfs(k, 0);
  for (int i = 1; i <= q; i++) {
    printf("%s\n", ans[i].c_str());
  }
  return 0;
}