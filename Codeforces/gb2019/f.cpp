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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;
const int S = 500;

int n, pre[maxn];
char s[maxn];

int cnt[(4 + S) * maxn];
ll small(int k) {
  cnt[n] = 1;
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += cnt[k * pre[i] - i + n];
    cnt[k * pre[i] - i + n]++;
  }
  for (int i = 1; i <= n; i++) {
    cnt[k * pre[i] - i + n]--;
  }
  return ans;
}
ll big() {
  ll ans = 0;
  vector<int> pos;
  for (int i = 1; i <= n; i++) if (s[i] == '1') pos.push_back(i);
  int cur = 0;
  for (int i = 1; i <= n; i++) {
    auto cal = [&i](int x, int c) {
      return x / c + (x % c >= (i - 1) % c);
    };
    for (int c = 1; c <= n / S && cur + c <= (int)pos.size(); c++) {
      int l = max(pos[cur + c - 1], S * c + i);
      int r = cur + c == (int)pos.size() ? n : pos[cur + c] - 1;
      if (l <= r) {
        ans += cal(r, c) - cal(l - 1, c);
      }
    }
    if (s[i] == '1') cur++;
  }
  return ans;
}

int main() {
  scanf("%s", s + 1); n = strlen(s + 1);
  for (int i = 1; i <= n; i++) {
    pre[i] = pre[i - 1];
    if (s[i] == '1') pre[i]++;
  }
  ll ans = big();
  for (int k = 1; k <= S; k++) {
    ans += small(k);
  }
  cout << ans;
  return 0;
}