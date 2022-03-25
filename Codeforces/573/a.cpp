#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
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
const int maxn = 100000 + 5;

ll n, m, k, p[maxn];

int main() {
    scanf("%I64d%I64d%I64d", &n, &m, &k);
    for (int i = 1; i <= m; i++) scanf("%I64d", p + i), p[i]--;
    ll tot = 0;
    int ans = 0;
    for (int i = 1; i <= m; ) {
        ll bel = (p[i] - tot) / k;
        int j = i;
        while (j <= m && (p[j] - tot) / k == bel) j++;
        ans++; i = j; tot = i - 1;
    }
    cout << ans;
    return 0;
}