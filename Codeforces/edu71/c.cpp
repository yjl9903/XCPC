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
const int maxn = 200000 + 5;

int n, a, b;
char s[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%s", &n, &a, &b, s + 1);
        ll res = 1ll * (n + 1) * b + 1ll * n * a;
        // dbg(res);
        int last = -1;
        for (int i = 1; i <= n; i++) {
            if (s[i] == '0') continue;
            if (last != -1) {
                // dbg(last, i);
                int len = i - last - 1;
                if (1ll * len * b <= 2ll * a) {
                    res -= 2ll * a;
                    res += 1ll * len * b;
                }
            }
            int j = i;
            while (j <= n && s[j] == '1') j++;
            res += 1ll * (j - i + 1) * b + 2ll * a;
            // dbg(i, j, 1ll * (j - i + 1) * b + 2ll * a);
            last = j; i = j - 1;
        }
        printf("%lld\n", res);
    }
    return 0;
}