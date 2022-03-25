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
const int maxn = 200000 + 5;

int p[27], fail[maxn], ans[maxn];
char s[maxn], t[maxn];

bool match(char x, char y) {
  if (x == y) return true;
  return p[x - 'a'] == y - 'a';
}

void getfail(int len, char* s) {
  fail[1] = 0;
  for (int i = 2; i <= len; i++) {
    int cur = fail[i - 1];
    while (cur > 0 && !match(s[cur + 1], s[i]))
      cur = fail[cur];
    if (match(s[cur + 1], s[i])) cur++;
    fail[i] = cur;
  }
}

int main() {
  for (int i = 0; i < 26; i++) {
    scanf("%d", p + i); p[i]--;
  }
  scanf("%s%s", s + 1, t + 1);
  int m = strlen(s + 1), n = strlen(t + 1);
  getfail(m, s);
  for (int i = 1, cur = 0; i <= n; i++) {
    while (cur > 0 && !match(t[i], s[cur + 1])) cur = fail[cur];
    if (match(s[cur + 1], t[i])) cur++;
    dbg(i, cur);
    if (cur == m) {
      dbg(i);
      ans[i] = true;
      cur = fail[cur];
    }
  }

  return 0;
}