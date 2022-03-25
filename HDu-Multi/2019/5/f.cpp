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
const int maxn = 1000000 + 5;

namespace exkmp {
    int nxt[maxn], extend[maxn];
    void getnxt(int n, char *s) {
        int p = 1, k = 2; nxt[1] = n;
        while (p + 1 <= n && s[p] == s[p + 1]) p++;
        nxt[2] = p - 1;
        for (int i = 3; i <= n; i++) {
            int len = nxt[i - k + 1];
            if (len + i <= p) nxt[i] = len;
            else {
                int j = max(p - i + 1, 0);
                while (i + j <= n && s[j + 1] == s[i + j]) j++;
                nxt[i] = j; k = i;
                p = i + j - 1;
            }
        }
    }
}
using namespace exkmp;

char s[maxn];
int n;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s", s + 1);
        n = strlen(s + 1);
        getnxt(n, s);
        ll ans = 0;
        for (int i = 2; i <= n; i++) {
            // dbg(i, nxt[i]);
            ans += nxt[i];
            if (nxt[i] < n - i + 1) ans++;
        }
        printf("%lld\n", ans);
    }
    return 0;
}