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
const int inf = 1 << 30;
const int maxn = 4000000 + 5;

char s[maxn];
map<char,string> f = {
  { '0', "0000" },
  { '1', "0001" },
  { '2', "0010" },
  { '3', "0011" },
  { '4', "0100" },
  { '5', "0101" },
  { '6', "0110" },
  { '7', "0111" },
  { '8', "1000" },
  { '9', "1001" },
  { 'A', "1010" },
  { 'B', "1011" },
  { 'C', "1100" },
  { 'D', "1101" },
  { 'E', "1110" },
  { 'F', "1111" }
};

bool a[maxn];
int solve(const string& s) {
  int ans = 0, n = s.length(), flag = true;
  for (int i = 0; i < n; i++) a[i] = s[i] - '0';
  for (int i = 1; i + 1 < n; i++) {
    if (a[i - 1]) {
      ans++;
      a[i - 1] ^= 1; a[i] ^= 1; a[i + 1] ^= 1;
    }
  }
  for (int i = 0; i < n && flag; i++) if (a[i]) flag = false;
  if (flag) {
    return ans;
  } else {
    return inf;
  }
}

char flip(char ch) {
  return ((ch - '0') ^ 1) + '0';
}

int main() {
  scanf("%s", s);
  string bit;
  for (int i = 0; s[i]; i++) bit += f[s[i]];
  int pos = 0; while (pos < (int)bit.length() && bit[pos] == '0') pos++;
  if (pos == (int)bit.length()) {
    puts("0"); return 0;
  }
  bit = bit.substr(pos);
  if ((int)bit.length() == 1) {
    printf("%d\n", int(bit[0] == '1'));
    return 0;
  }
  if ((int)bit.length() == 2) {
    if (bit[0] == bit[1]) {
      printf("%d\n", int(bit[0] == '1'));
    } else {
      puts("No");
    }
    return 0;
  }

  int n = bit.length(), ans = solve(bit);
  bit[0] = flip(bit[0]); bit[1] = flip(bit[1]);
  ans = min(ans, solve(bit) + 1);
  bit[n - 1] = flip(bit[n - 1]); bit[n - 2] = flip(bit[n - 2]);
  ans = min(ans, solve(bit) + 2);
  bit[0] = flip(bit[0]); bit[1] = flip(bit[1]);
  ans = min(ans, solve(bit) + 1);

  if (ans >= inf) puts("No");
  else printf("%d\n", ans);
  return 0;
}