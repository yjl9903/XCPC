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
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 600000 + 5;

int q, n, s[maxn], fail[maxn];
vector<int> del[maxn];

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1
  int mn[maxn * 4];
  void build(int l = 1, int r = q, int rt = 1) {
    if (l == r) {
      mn[rt] = inf; return ;
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
  }
  void update(int pos, int val, int l = 1, int r = q, int rt = 1) {
    if (l == r) {
      mn[rt] = val; return ;
    }
    int m = (l + r) / 2;
    if (pos <= m) update(pos, val, lson);
    else update(pos, val, rson);
    mn[rt] = min(mn[rt << 1], mn[rt << 1 | 1]);
  }
  int query(int L, int R, int l = 1, int r = q, int rt = 1) {
    if (L <= l && r <= R) return mn[rt];
    int m = (l + r) / 2, ans = inf;
    if (L <= m) ans = query(L, R, lson);
    if (R > m) ans = min(ans, query(L, R, rson));
    return ans;
  }
}

ull sum;
map<int,int> mp;
void push(int x) {
  sum += x; mp[x]++;
}
void pop(int x) {
  sum -= x; mp[x]--;
}
void updateMin(int x) {
  for (auto it = mp.upper_bound(x); it != mp.end(); it++) {
    mp[x] += it->second;
    sum += 1ll * (x - it->first) * it->second;
  }
  while (!mp.empty() && mp.rbegin()->first > x) {
    auto it = mp.end();
    mp.erase(--it);
  }
}

int main() {
  scanf("%d", &q);
  SegT::build();
  ull ans = 0;
  for (n = 1; n <= q; n++) {
    char c[2]; int w;
    scanf("%s%d", c, &w);
    s[n] = (c[0] - 'a' + ans) % 26;
    w ^= (ans & ((1 << 30) - 1));

    SegT::update(n, w);
    updateMin(w);

    if (n == 1) {
      push(w); ans += sum;
      printf("%I64u\n", ans);
      continue;
    }

    int cur = fail[n - 1];
    while (cur && s[cur + 1] != s[n]) {
      del[n].push_back(cur + 1); // length
      cur = fail[cur];
    }
    if (s[cur + 1] == s[n]) cur++;
    fail[n] = cur;
    for (int x: del[cur]) del[n].push_back(x);

    if (s[1] == s[n]) push(w);

    for (int x: del[n]) pop(SegT::query(n - x + 1, n));
    
    printf("%I64u\n", ans += sum);
  }
  return 0;
}