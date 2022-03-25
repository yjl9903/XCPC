#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
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
const int maxn = 1000000 + 5;

int n; ll k;
char s[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%I64d%s", &n, &k, s + 1);
    vector<int> zero;
    for (int i = 1; i <= n; i++) if (s[i] == '0') zero.push_back(i);
    string ans(s + 1);
    ll sum = 0;
    for (int i = 0; i < (int)zero.size(); i++) {
      int need = zero[i] - i - 1;
      if (sum + need > k) {
        string res;
        for (int j = 0; j < i; j++) res += '0';
        for (int j = 0; j < zero[i] - i - 1 - k + sum; j++) res += '1';
        res += '0';
        for (int j = 0; j < k - sum; j++) res += '1';
        for (int j = zero[i] + 1; j <= n; j++) res += s[j];
        ans = res;
        break;
      }
      sum += need;
      if (i + 1 == (int)zero.size()) {
        string res;
        for (int j = 0; j < (int)zero.size(); j++) res += '0';
        for (int j = 0; j < n - (int)zero.size(); j++) res += '1';
        ans = res;
        break;
      }
    }
    printf("%s\n", ans.c_str());
  }
  return 0;
}