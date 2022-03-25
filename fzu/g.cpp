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
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

const unsigned int mask32 = ~0u;
const int seed = 133;
const int p1 = 998244353;
const int p2 = 91815541;

ull xp1[maxn], xp2[maxn];

struct Hash_t {
  ull val;

  Hash_t(ull x = 0): val(x) {}

  Hash_t(ull x, ull y): val(x | (y << 32)) {}

  bool operator== (const Hash_t& rhs) const {
    return val == rhs.val;
  }

  ull first() const {
    return val & mask32;
  }

  ull second() const {
    return val >> 32;
  }

  Hash_t operator+(const Hash_t& rhs) const {
    ull a = (first() + rhs.first()) % p1;
    ull b = (second() + rhs.second()) % p2;
    return Hash_t(a, b);
  }

  Hash_t mul(int len) {
    ull a = val & mask32, b = val >> 32;
    a = a * xp1[len] % p1;
    b = b * xp2[len] % p2;
    return Hash_t(a, b);
  }
} ori, rev;

int n, q, ansT;
bool ans[maxn];

Hash_t pushFront(Hash_t hsh, char ch) {
  return hsh.mul(1) + Hash_t(ch, ch);
}

Hash_t pushBack(Hash_t hsh, char ch) {
  return Hash_t(ch, ch).mul(n) + hsh;
}

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  Hash_t a[maxn << 3];
  int tag[maxn << 3];

  void pushdown(int rt) {
    if (tag[rt] == 0) return ;
    int t = tag[rt];
    a[rt << 1] = a[rt << 1].mul(t);
    a[rt << 1 | 1] = a[rt << 1 | 1].mul(t);
    tag[rt << 1] += t;
    tag[rt << 1 | 1] += t;
    tag[rt] = 0;
  }

  void clear(int l = 0, int r = q + q + 2, int rt = 1) {
    tag[rt] = 0;
    a[rt].val = 0;
    if (l == r) return ;
    int m = (l + r) / 2;
    clear(lson);
    clear(rson);
  }

  void set(int p, const Hash_t& hsh, int l = 0, int r = q + q + 2, int rt = 1) {
    if (l == r) {
      a[rt] = hsh;
      return ;
    }
    int m = (l + r) / 2;
    pushdown(rt);
    if (p <= m) set(p, hsh, lson);
    else set(p, hsh, rson);
    a[rt] = a[rt << 1] + a[rt << 1 | 1];
  }

  void add(int L, int R, int l = 0, int r = q + q + 2, int rt = 1) {
    if (L <= l && r <= R) {
      a[rt] = a[rt].mul(1);
      tag[rt]++;
      return ;
    }
    int m = (l + r) / 2;
    pushdown(rt);
    if (L <= m) add(L, R, lson);
    if (R > m) add(L, R, rson);
    a[rt] = a[rt << 1] + a[rt << 1 | 1];
  }

  Hash_t query(int L, int R, int l = 0, int r = q + q + 2, int rt = 1) {
    if (L <= l && r <= R) {
      return a[rt];
    }
    int m = (l + r) / 2;
    Hash_t ans;
    pushdown(rt);
    if (L <= m) ans = ans + query(L, R, lson);
    if (R > m) ans = ans + query(L, R, rson);
    return ans;
  }
}

int main() {
  xp1[0] = xp2[0] = 1;
  for (int i = 1; i < maxn; i++) {
    xp1[i] = xp1[i - 1] * seed % p1;
    xp2[i] = xp2[i - 1] * seed % p2;
  }

  while (scanf("%d", &q) == 1) {
    SegT::clear();
    ori.val = 0;
    rev.val = 0;
    n = 0;
    ansT = 0;
    
    int L = q + 1, R = q;
    int p1, p2 = 3;

    // string str;

    for (int i = 1; i <= q; i++) {
      char ch[3];
      scanf("%d", &p1);
      int op = p1 ^ p2;
      // dbg(op);
      if (op == 0) {
        scanf("%s", ch);
        // str = ch[0] + str;
        ori = pushFront(ori, ch[0]);
        rev = pushBack(rev, ch[0]);

        if (L <= R) {
          SegT::add(L, R);
        }
        SegT::set(--L, Hash_t(ch[0], ch[0]));
        n++;
      } else if (op == 1) {
        scanf("%s", ch);
        // str += ch[0];
        ori = pushBack(ori, ch[0]);
        rev = pushFront(rev, ch[0]);

        SegT::set(++R, Hash_t(ch[0], ch[0]).mul(n));
        n++;
      } else if (op == 2) {
        int per;
        scanf("%d", &per);
        
        Hash_t a = SegT::query(L, L + (n - per) - 1);
        assert(L + per == R - (n - per) + 1);
        Hash_t b = SegT::query(R - (n - per) + 1, R);
        // dbg(a.mul(per).val, b.val);
        bool ans = a.mul(per) == b;
        if (ans) {
          // printf("Yes");
          ::ans[++ansT] = 1;
          p2 = ((p2 & 1) << 1) | 1;
        } else {
          // printf("No");
          ::ans[++ansT] = 0;
          p2 = ((p2 & 1) << 1);
        }
      } else if (op == 3) {
        bool ans = ori == rev;
        if (ans) {
          // printf("Yes");
          ::ans[++ansT] = 1;
          p2 = ((p2 & 1) << 1) | 1;
        } else {
          // printf("No");
          ::ans[++ansT] = 0;
          p2 = ((p2 & 1) << 1);
        }
      }
    }

    for (int i = 1; i <= ansT; i++) {
      printf(ans[i] ? "Yes" : "No");
      if (i < ansT) printf("\n");
    }
  }
  return 0;
}