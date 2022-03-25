#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <map>
#include <unordered_map>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int seed = 135;
const int p1 = 998244353, p2 = 19260817;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxr = 500 + 5;
const int maxn = 200000 + 5;

ull xp1[maxn], xp2[maxn], xp[maxn];

int n, m, q, ans[maxn];
char s[maxr][maxr], tmp[maxn];

struct Hash {
  static void init() {
    xp1[0] = xp2[0] = xp[0] = 1;
    for (int i = 1; i < maxn; ++i) {
      xp1[i] = xp1[i - 1] * seed % p1;
      xp2[i] = xp2[i - 1] * seed % p2;
      xp[i] = xp[i - 1] * seed;
    }
  }

  ull h[maxr];
  ull build(int n, const char* s) {
    ull r1 = 0, r2 = 0;
    for (int i = 1; i <= n; i++) {
      r1 = (r1 * seed + s[i]) % p1;
      r2 = (r2 * seed + s[i]) % p2;
      h[i] = (r1 << 32) | r2;
    }
    return h[n];
  }
  ull build2(int c) {
    ull r1 = 0, r2 = 0;
    for (int i = 1; i <= n; i++) {
      r1 = (r1 * seed + s[i][c]) % p1;
      r2 = (r2 * seed + s[i][c]) % p2;
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
            ((right2 - left2 * xp2[len] % p2 + p2) % p2);
  }
} row[maxr], col[maxr];

ull offset(ull a, ull b, int len) {
  unsigned int mask32 = ~(0u);
  ull a1 = a >> 32, a2 = a & mask32;
  ull b1 = b >> 32, b2 = b & mask32;
  return (((b1 + a1 * xp1[len] % p1) % p1) << 32) | 
          ((b2 + a2 * xp2[len] % p2) % p2);
}

ull ghsh(const string& s) {
  ull r1 = 0, r2 = 0;
  for (int i = 0; i < (int)s.length(); i++) {
    r1 = (r1 * seed + s[i]) % p1;
    r2 = (r2 * seed + s[i]) % p2;
  }
  return (r1 << 32) | r2;
}

unordered_map<ull,int> prework(int len) {
  unordered_map<ull,int> mp;
  int flag = 1;
  for (int i = 1; i <= n && flag; i++) {
    for (int j = 1; j <= m; j++) {
      if (max(1, n - i - len) > min(len, m - j + 1)) {
        flag = 0; break;
      }
      for (int l = max(1, n - i - len); l <= len && j + l - 1 <= m; l++) {
        ull r = row[i].query(j, j + l - 1);
        if (l == len) {
          mp[r]++;
        } else {
          ull c = col[j + l - 1].query(i + 1, i + len - l);
          mp[offset(r, c, len - l)]++;
        }
      }
    }
  }
  return mp;
}

int main() {
  Hash::init();
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s[i] + 1);
  }
  for (int i = 1; i <= n; i++) {
    row[i].build(m, s[i]);
  }
  for (int i = 1; i <= m; i++) {
    col[i].build2(i);
  }

  vector<pair<string,int> > que;
  for (int i = 1; i <= q; i++) {
    scanf("%s", tmp);
    if (strlen(tmp) >= n + m) continue;
    que.push_back(make_pair(string(tmp), i));
  }
  sort(begin(que), end(que), [](pair<string,int>& a, pair<string,int>& b) {
    return a.first.length() < b.first.length();
  });
  for (int i = 0, j; i < (int)que.size(); i = j) {
    j = i;
    int len = que[i].first.length();
    auto mp = prework(len);
    while (j < (int)que.size() && len == (int)que[j].first.length()) {
      ans[que[j].second] = mp[ghsh(que[j].first)]; j++;
    }
  }
  for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
  return 0;
}