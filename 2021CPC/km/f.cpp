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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 2000000 + 5;

inline int add(int x, int y) {
  x += y;
  return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
  x -= y;
  return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
  return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
  int r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x % mod;
    n >>= 1; x = 1ll * x * x % mod;
  }
  return r;
}
inline int inv(int x) {
  return qpow(x, mod - 2);
}

int n, q, V[maxn];
char s[maxn];

namespace pam {
  static const int S = 26;

  int sz, tot, val[maxn];
  int len[maxn], ch[maxn][S], fail[maxn], cnt[maxn];
  int go[maxn][S], dep[maxn], link[maxn][20];
  char s[maxn];

  int node(int l) {
    sz++;
    ms(ch[sz], 0);
    len[sz] = l;
    fail[sz] = cnt[sz] = 0;
    return sz;
  }
  void clear() {
    sz = -1;
    s[tot = 0] = '$';
    node(0);
    node(-1);
    fail[0] = 1;
    for (int i = 0; i < S; i++) {
      go[0][i] = 1;
    }
    ms(link[0], 0);
  }
  int jump(int tot, int len) {
    for (int j = 19; j >= 0; j--) {
      int u = link[tot][j];
      if (dep[u] >= len) {
        tot = u;
      }
    }
    return tot;
  }
  int getfail(int x) {
    if (s[tot] == s[jump(tot, dep[tot] - len[x] - 1)]) {
      return x;
    } else {
      return go[x][s[tot] - 'a'];
    }
  }
  int insert(char c, int fa, int last = 0) {
    s[++tot] = c;
    dep[tot] = dep[fa] + 1;
    link[tot][0] = fa;
    for (int i = 1; i < 20; i++) {
      link[tot][i] = link[link[tot][i - 1]][i - 1];
    }
    int now = getfail(last);
    if (!ch[now][c - 'a']) {
      int x = node(len[now] + 2);
      fail[x] = ch[getfail(fail[now])][c - 'a'];
      ch[now][c - 'a'] = x;

      // maintain some info...
      val[x] = add(V[len[x]], val[fail[x]]);

      memcpy(go[x], go[fail[x]], sizeof go[x]);
      go[x][s[jump(tot, dep[tot] - len[fail[x]])] - 'a'] = fail[x];
    }
    last = ch[now][c - 'a'];
    cnt[last]++;
    return last;
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    pam::clear();
    scanf("%d%d%s", &n, &q, s + 1);
    vector<int> stk { 0 }, ans { 0 }, tot { 0 };
    int len = strlen(s + 1), m = len;
    for (int i = 1; i <= len + q; i++) {
      if (i <= n) {
        V[i] = mul(n - i + 1, qpow(26, n - i));
      } else {
        V[i] = 0;
      }
    }
    for (int i = 1; i <= len; i++) {
      int u = pam::insert(s[i], tot.back(), stk.back());
      int nxt = add(ans.back(), pam::val[u]);
      stk.push_back(u);
      tot.push_back(i);
      ans.push_back(nxt);
    }
    printf("%d\n", ans.back());
    for (int i = 1; i <= q; i++) {
      int op;
      scanf("%d", &op);
      if (op == 1) {
        char ch[2];
        scanf("%s", ch);
        int u = pam::insert(ch[0], tot.back(), stk.back());
        int nxt = add(ans.back(), pam::val[u]);
        stk.push_back(u);
        tot.push_back(++m);
        ans.push_back(nxt);
        len++;
      } else if (op == 2) {
        stk.pop_back();
        tot.pop_back();
        ans.pop_back();
        len--;
      }
      printf("%d\n", ans.back());
    }
  }
  return 0;
}