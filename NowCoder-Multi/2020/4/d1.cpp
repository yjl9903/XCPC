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
using ull = unsigned long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;
const int seed = 135;
const int p1 = 1e9 + 7, p2 = 1e9 + 9;
 
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
} hsh, h10, h99;
 
int get(char a, char b) {
  return 10 * (a - '0') + (b - '0');
}
 
int n;
char s[maxn];
 
int main() {
  Hash::init();
  s[1] = '1';
  for (int i = 2; i <= 200000; i++) s[i] = '0';
  h10.build(200000, s);
  for (int i = 1; i <= 200000; i++) s[i] = '9';
  h99.build(200000, s);
 
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%s", &n, s + 1);
    hsh.build(n, s);
 
    char mx = '0', mn = '9';
    for (int i = 1; i <= n; i++) {
      mx = max(mx, s[i]);
      mn = min(mn, s[i]);
    }
    int ans = mx - mn;
 
    if (s[1] != '0') {
      bool cas1 = s[1] == '1', cas9 = s[1] == '9';
      for (int i = 2; i + i <= n + 1; i++) {
        bool valid = true;
        if (cas1) {
          int j = i + 1;
          int mx = s[i] - '0', mn = mx;
          while (j <= n) {
            if (s[j] == '0') {
              valid = false;
              break;
            }
            if (j + i - 1 <= n && hsh.query(j, j + i - 2) == h10.query(1, i - 1)) {
              // case: 10000x
              int tot = s[j + i - 1] - '0';
              mx = max(mx, tot);
              mn = min(mn, tot);
              j += i;
            } else if (j + i - 2 <= n && (i == 2 || hsh.query(j, j + i - 3) == h99.query(1, i - 2))) {
              // case: 99999x; (i - 2) * 9
              int tot = s[j + i - 2] - '0';
              mx = max(mx, tot - 10);
              mn = min(mn, tot - 10);
              j += i - 1;
            } else {
              valid = false;
              break;
            }
          }
 
          if (valid && j == n + 1) {
            ans = min(ans, mx - mn);
          }
        } else if (cas9) {
          int j = i + 1;
          int mx = (s[i] - '0') - 10, mn = mx;
          while (j <= n) {
            if (s[j] == '0') {
              valid = false;
              break;
            }
            if (j + i <= n && hsh.query(j, j + i - 1) == h10.query(1, i)) {
              // case: 10000x, 1000.. length: i
              int tot = s[j + i] - '0';
              mx = max(mx, tot);
              mn = min(mn, tot);
              j += i + 1;
            } else if (j + i - 1 <= n && hsh.query(j, j + i - 2) == h99.query(1, i - 1)) {
              // case: 99999x; (i - 1) * 9
              int tot = s[j + i - 1] - '0';
              mx = max(mx, tot - 10);
              mn = min(mn, tot - 10);
              j += i;
            } else {
              valid = false;
              break;
            }
          }
 
          if (valid && j == n + 1) {
            ans = min(ans, mx - mn);
          }
        } else {
          if (n % i) continue;
          ull hsVal = 0;
          if (i > 2) {
            hsVal = hsh.query(1, i - 2);
          }
          int mx = get(s[i - 1], s[i]), mn = mx;
          for (int j = i + 1; j + i - 1 <= n; j += i) {
            if (s[j] == '0') {
              valid = false;
              break;
            }
            if (i > 2) {
              if (hsh.query(j, j + i - 3) != hsVal) {
                valid = false;
                break;
              }
            }
            int tot = get(s[j + i - 2], s[j + i - 1]);
            mx = max(mx, tot);
            mn = min(mn, tot);
          }
          if (valid) {
            ans = min(ans, mx - mn);
          }
        }
 
        cas1 &= s[i] == '0';
        cas9 &= s[i] == '9';
      }
    }
 
    printf("%d\n", ans);
  }
  return 0;
}