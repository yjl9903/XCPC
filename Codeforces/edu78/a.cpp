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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int main() {
  int T; cin >> T;
  while (T--) {
    string s, t;
    cin >> s >> t;
    vector<int> cnt(26);
    for (auto& x: s) cnt[x - 'a']++;
    int flag = 0;
    for (int i = 0; i < (int)t.length(); i++) {
      vector<int> sum(26);
      for (int j = 0; j < (int)s.length() && i + j < (int)t.length(); j++) {
        sum[t[i + j] - 'a']++;
      }
      if (sum == cnt) {
        flag = 1; break;
      }
    }
    if (flag) puts("YES");
    else puts("NO");
  }
  return 0;
}