#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <cassert>
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
const int maxn = 10000000 + 5;

int n, a, b, fail[maxn];
char s[maxn];

int main() {
    while (scanf("%d%d%s", &a, &b, s + 1) == 3) {
        n = strlen(s + 1); int st = -1;
        for (int i = 1; i <= n; i++) {
            if (s[i] == '.') {
                st = i; break;
            }
        }
        assert(st != -1);
        for (int i = st + 1; i <= n; i++) s[i - st] = s[i];
        n = n - st; s[n + 1] = 0;
        // dbg(s + 1, n);
        // cout << s + 1 << endl;
        reverse(s + 1, s + 1 + n);
        fail[1] = 0;
        for (int i = 2; i <= n; i++) {
            int cur = fail[i - 1];
            while (cur && s[cur + 1] != s[i]) cur = fail[cur];
            if (s[cur + 1] == s[i]) cur++;
            fail[i] = cur;
        }
        ll ans = -1e18;
        for (int i = 1; i <= n; i++) {
            ll tot = 1ll * a * i - 1ll * b * (i - fail[i]);
            // dbg(i, fail[i], tot);
            ans = max(ans, tot);
        }
        printf("%lld\n", ans);
    }
    return 0;
}